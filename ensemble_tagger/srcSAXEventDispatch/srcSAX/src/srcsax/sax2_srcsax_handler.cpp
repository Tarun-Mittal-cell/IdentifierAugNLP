/**
 *  @file sax2_srcsax_handler.cpp
 *
 * @copyright Copyright (C) 2013-2014 srcML, LLC. (www.srcML.org)
 *
 * This file is part of the srcML SAX2 Framework.
 *
 * The srcML SAX2 Framework is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML SAX2 Framework is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.

 *  You should have received a copy of the GNU General Public License
 * along with the srcML SAX2 Framework; if not, write to the Free Software
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

#include <sax2_srcsax_handler.hpp>
#include <windows_utils.hpp>

#include <cstring>

/** Static sax handler for zero initializing in factory */
xmlSAXHandler sax2_srcml_handler_init;

/**
 * factory
 *
 * Create SAX handler.
 */
xmlSAXHandler srcsax_sax2_factory() {

    xmlSAXHandler sax = sax2_srcml_handler_init;

    sax.initialized    = XML_SAX2_MAGIC;

    sax.startDocument = &start_document;
    sax.endDocument = &end_document;

    sax.startElementNs = &start_root;
    sax.endElementNs = &end_element_ns;

    sax.characters = &characters_first;
    sax.ignorableWhitespace = &characters_first;

    sax.comment = &comment;
    sax.cdataBlock = &cdata_block;
    sax.processingInstruction = &processing_instruction;

    return sax;
}

#pragma GCC diagnostic push
#pragma GCC diagnostic ignored "-Wunused-parameter"

/**
 * libxml2_namespaces2srcsax_namespaces
 * @param number_namespaces the number of namespaces
 * @param libxml2_namespaces
 *
 * Helper function to convert the libxml2 namespaces to srcsax namespaces
 * returning a dynamically allocated struct containing the namespaces.
 *
 * @returns the converted namespaces as srcsax_namespace.
 */
static inline srcsax_namespace * libxml2_namespaces2srcsax_namespaces(int number_namespaces, const xmlChar ** libxml2_namespaces) {

    struct srcsax_namespace * srcsax_namespaces = (srcsax_namespace *)calloc(number_namespaces, sizeof(srcsax_namespace));

    for(int pos = 0, index = 0; pos < number_namespaces; ++pos, index += 2) {

        srcsax_namespaces[pos].prefix = (const char *)libxml2_namespaces[index];
        srcsax_namespaces[pos].uri = (const char *)libxml2_namespaces[index + 1];

    }

    return srcsax_namespaces;
}

/**
 * free_srcsax_namespaces
 * @param number_namespaces the number of namespaces (not currently used)
 * @param libxml2_namespaces
 *
 * Helper function to free srcsax_namespace * struct allocated by libxml2_namespaces2srcsax_namespaces.
 */
static inline void free_srcsax_namespaces(int /*number_namespaces*/, srcsax_namespace * namespaces) {

    free((void *)namespaces);

}

/**
 * libxml2_attributes2srcsax_attributes
 * @param number_attributes the number of attributes
 * @param libxml2_attributes
 *
 * Helper function to convert the libxml2 attributes to srcsax attributes
 * returning a dynamically allocated struct containing the attributes.
 *
 * @returns the converted attributes as srcsax_attribute.
 */
static inline srcsax_attribute * libxml2_attributes2srcsax_attributes(int number_attributes, const xmlChar ** libxml2_attributes) {

    struct srcsax_attribute * srcsax_attributes = (srcsax_attribute *)calloc(number_attributes, sizeof(srcsax_attribute));

    for(int pos = 0, index = 0; pos < number_attributes; ++pos, index += 5) {

        srcsax_attributes[pos].localname = (const char *)libxml2_attributes[index];
        srcsax_attributes[pos].prefix = (const char *)libxml2_attributes[index + 1];
        srcsax_attributes[pos].uri = (const char *)libxml2_attributes[index + 2];
        srcsax_attributes[pos].value = strndup((const char *)libxml2_attributes[index + 3], libxml2_attributes[index + 4] - libxml2_attributes[index + 3]);

    }

    return srcsax_attributes;
}

/**
 * free_srcsax_attributes
 * @param number_attributes the number of attributes
 * @param libxml2_attributes
 *
 * Helper function to free srcsax_attribute * struct allocated by libxml2_attributes2srcsax_attributes.
 */
static inline void free_srcsax_attributes(int number_attributes, srcsax_attribute * attributes) {

    for(int pos = 0; pos < number_attributes; ++pos)
        free((void *)attributes[pos].value);

    free((void *)attributes);

}

/** 
 * srcml_element_stack_push
 * @param context the srcsax_context
 * @param srcml_element_stack the stack
 * @param prefix the prefix of the element to push
 * @param localname the name of the element to push
 *
 * Push the element on to the stack.
 */
 void srcml_element_stack_push(srcsax_context * context, std::vector<const char *> & srcml_element_stack, const char * prefix, const char * localname) {

    size_t prefix_length = prefix ? strlen(prefix) : 0;
    size_t name_length = strlen(localname);
    size_t srcml_element_length = prefix ? prefix_length + name_length + 1 : name_length;
    char * srcml_element_string = (char *)calloc(srcml_element_length + 1, sizeof(char));

    size_t offset = 0;
    if(prefix) {

        strncat(srcml_element_string, prefix, prefix_length);
        srcml_element_string[prefix_length] = ':';
        offset = prefix_length + 1;

    }

    strncat(srcml_element_string + offset, localname, name_length);

    srcml_element_stack.push_back(srcml_element_string);

    context->stack_size = srcml_element_stack.size();
    context->srcml_element_stack = &srcml_element_stack.front();

 }

/** 
 * srcml_element_stack_pop
 * @param context the srcsax_context
 * @param srcml_element_stack the stack
 *
 * Pop an element off the stack.
 */
 void srcml_element_stack_pop(srcsax_context * context, std::vector<const char *> & srcml_element_stack) {

    if(srcml_element_stack.size() == 0) return;

    const char * srcml_element = srcml_element_stack.back();

    srcml_element_stack.pop_back();

    free((void *)srcml_element);

    context->stack_size = srcml_element_stack.size();
    if(context->stack_size == 0)
        context->srcml_element_stack = 0;
    else
        context->srcml_element_stack = &srcml_element_stack.front();

 }

/**
 * start_document
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for start of document.
 * Immediately calls supplied handlers function.
 */
void start_document(void * ctx) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    state->context->stack_size = 0;
    state->context->srcml_element_stack = 0;

    state->context->encoding = "UTF-8";
    if(ctxt->encoding && ctxt->encoding[0]!= '\0')
        state->context->encoding = (const char *)ctxt->encoding;
    else if(ctxt->input)
        state->context->encoding = (const char *)ctxt->input->encoding;

    if(state->context->terminate) return;

    if(state->context->handler->start_document)
        state->context->handler->start_document(state->context);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

}

/**
 * end_document
 * @param ctx an xmlParserCtxtPtr
 *
 * SAX handler function for end of document.
 * Calls end_root if needed then
 * immediately calls supplied handlers function.
 */
void end_document(void * ctx) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    state->context->stack_size = 0;
    state->context->srcml_element_stack = 0;

    if(state->context->terminate) return;

    if(state->mode != END_ROOT && state->mode != START && state->context->handler->end_root)
        state->context->handler->end_root(state->context, (const char *)state->root.localname, (const char *)state->root.prefix, (const char *)state->root.URI);

    if(state->context->terminate) return;

    if(state->context->handler->end_document)
        state->context->handler->end_document(state->context);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

}

/**
 * start_root
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of root element.
 * Caches root info and immediately calls supplied handlers function.
 */
void start_root(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
               int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
               const xmlChar ** attributes) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)prefix, (const char *)localname);

    state->root = srcml_element(state->context, localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes);

    state->mode = ROOT;

    // handle nested units
    ctxt->sax->startElementNs = &start_element_ns_first;

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

}

/**
 * start_element_ns_first
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of first element after root
 * Detects archive and acts accordingly.
 */
void start_element_ns_first(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                         int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                         const xmlChar ** attributes) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    int ns_length = state->root.nb_namespaces * 2;
    for (int i = 0; i < ns_length; i += 2)
        if(prefix && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)prefix) == 0)
            prefix = state->root.namespaces[i];

    for (int i = 1; i < ns_length; i += 2)
        if(URI && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)URI) == 0)
            URI = state->root.namespaces[i];

    if(strcmp((const char *)localname, "macro-list") == 0) {

        if(state->context->handler->meta_tag)
            state->meta_tags.push_back(srcml_element(state->context, localname, prefix, URI, nb_namespaces, namespaces, nb_attributes, nb_defaulted, attributes));

        return;

    }

    srcsax_namespace * srcsax_namespaces = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(nb_namespaces, namespaces);
    srcsax_attribute * srcsax_attributes = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(nb_attributes, attributes);

    state->is_archive = strcmp((const char *)localname, "unit") == 0;
    state->context->is_archive = state->is_archive;

    if(state->context->terminate) return;

    if(state->context->handler->start_root) {

        srcsax_namespace * srcsax_namespaces_root = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(state->root.nb_namespaces, state->root.namespaces);
        srcsax_attribute * srcsax_attributes_root = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(state->root.nb_attributes, state->root.attributes);
        state->context->handler->start_root(state->context, (const char *)state->root.localname, (const char *)state->root.prefix, (const char *)state->root.URI,
                                            state->root.nb_namespaces, srcsax_namespaces_root, state->root.nb_attributes,
                                            srcsax_attributes_root);

        free_srcsax_namespaces(state->root.nb_namespaces, srcsax_namespaces_root);
        free_srcsax_attributes(state->root.nb_attributes, srcsax_attributes_root);

    }

    if(state->context->terminate) return;

    if(state->context->handler->meta_tag && !state->meta_tags.empty()) {

        for(std::vector<srcml_element>::const_iterator citr = state->meta_tags.begin(); citr < state->meta_tags.end(); ++citr) {

            if(state->context->terminate) return;

            srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)citr->prefix, (const char *)citr->localname);

            srcsax_namespace * srcsax_namespaces_meta_tag = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(citr->nb_namespaces, citr->namespaces);
            srcsax_attribute * srcsax_attributes_meta_tag = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(citr->nb_attributes, citr->attributes);  

            state->context->handler->meta_tag(state->context, (const char *)citr->localname, (const char *)citr->prefix, (const char *)citr->URI,
                                                citr->nb_namespaces, srcsax_namespaces_meta_tag, citr->nb_attributes,
                                                srcsax_attributes_meta_tag);

            free_srcsax_namespaces(citr->nb_namespaces, srcsax_namespaces_meta_tag);
            free_srcsax_attributes(citr->nb_attributes, srcsax_attributes_meta_tag);

            srcml_element_stack_pop(state->context, state->srcml_element_stack);

        }

    }

    if(state->context->terminate) return;

    if(!state->is_archive) {

        ++state->context->unit_count;

        if(state->context->terminate) return;

        state->mode = UNIT;

        if(state->context->handler->start_unit) {

            srcsax_namespace * srcsax_namespaces_root = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(state->root.nb_namespaces, state->root.namespaces);
            srcsax_attribute * srcsax_attributes_root = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(state->root.nb_attributes, state->root.attributes);        
            state->context->handler->start_unit(state->context, (const char *)state->root.localname, (const char *)state->root.prefix, (const char *)state->root.URI,
                                                state->root.nb_namespaces, srcsax_namespaces_root, state->root.nb_attributes,
                                                srcsax_attributes_root);

            free_srcsax_namespaces(state->root.nb_namespaces, srcsax_namespaces_root);
            free_srcsax_attributes(state->root.nb_attributes, srcsax_attributes_root);

        }

        if(state->context->terminate) return;

        if(state->characters.size() != 0 && state->context->handler->characters_unit)
            state->context->handler->characters_unit(state->context, state->characters.c_str(), (int)state->characters.size());

        if(state->context->terminate) return;

        srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)prefix, (const char *)localname);

        if(state->context->handler->start_element)
            state->context->handler->start_element(state->context, (const char *)localname, (const char *)prefix, (const char *)URI,
                                                      nb_namespaces, srcsax_namespaces, nb_attributes, srcsax_attributes);
    } else {

        if(state->context->terminate) return;
        
        if(state->context->handler->characters_root)
            state->context->handler->characters_root(state->context, state->characters.c_str(), (int)state->characters.size());

        ++state->context->unit_count;

        srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)prefix, (const char *)localname);

        if(state->context->terminate) return;

        state->mode = UNIT;
        if(state->context->handler->start_unit)
            state->context->handler->start_unit(state->context, (const char *)localname, (const char *)prefix, (const char *)URI,
                                                nb_namespaces, srcsax_namespaces, nb_attributes, srcsax_attributes);


    }

    if(state->context->terminate) return;

    if(ctxt->sax->startElementNs) ctxt->sax->startElementNs = &start_element_ns;
    if(ctxt->sax->characters) {

        ctxt->sax->characters = &characters_unit;
        ctxt->sax->ignorableWhitespace = &characters_unit;

    }

    free_srcsax_namespaces(nb_namespaces, srcsax_namespaces);
    free_srcsax_attributes(nb_attributes, srcsax_attributes);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

}

/**
 * start_unit
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of an unit.
 * Immediately calls supplied handlers function.
 */
void start_unit(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
               int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
               const xmlChar ** attributes) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    if(state->context->terminate) return;

    srcsax_namespace * srcsax_namespaces = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(nb_namespaces, namespaces);
    srcsax_attribute * srcsax_attributes = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(nb_attributes, attributes);

    srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)prefix, (const char *)localname);

    int ns_length = state->root.nb_namespaces * 2;
    for (int i = 0; i < ns_length; i += 2)
        if(prefix && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)prefix) == 0)
            prefix = state->root.namespaces[i];

    for (int i = 1; i < ns_length; i += 2)
        if(URI && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)URI) == 0)
            URI = state->root.namespaces[i];

    ++state->context->unit_count;

    state->mode = UNIT;



    if(state->context->handler->start_unit)
        state->context->handler->start_unit(state->context, (const char *)localname, (const char *)prefix, (const char *)URI,
            nb_namespaces, srcsax_namespaces, nb_attributes, srcsax_attributes);

    if(ctxt->sax->startElementNs) ctxt->sax->startElementNs = &start_element_ns;
    if(ctxt->sax->characters) {

        ctxt->sax->characters = &characters_unit;
        ctxt->sax->ignorableWhitespace = &characters_unit;

    }

    free_srcsax_namespaces(nb_namespaces, srcsax_namespaces);
    free_srcsax_attributes(nb_attributes, srcsax_attributes);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

}

/**
 * start_element_ns
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 * @param nb_namespaces number of namespaces definitions
 * @param namespaces the defined namespaces
 * @param nb_attributes the number of attributes on the tag
 * @param nb_defaulted the number of defaulted attributes
 * @param attributes list of attribute name value pairs (localname/prefix/URI/value/end)
 *
 * SAX handler function for start of an element.
 * Immediately calls supplied handlers function.
 */
void start_element_ns(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI,
                    int nb_namespaces, const xmlChar ** namespaces, int nb_attributes, int nb_defaulted,
                    const xmlChar ** attributes) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;
    
    if(state->context->terminate) return;

    srcsax_namespace * srcsax_namespaces = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(nb_namespaces, namespaces);
    srcsax_attribute * srcsax_attributes = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(nb_attributes, attributes);

    srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)prefix, (const char *)localname);

    int ns_length = state->root.nb_namespaces * 2;
    for (int i = 0; i < ns_length; i += 2)
        if(prefix && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)prefix) == 0)
            prefix = state->root.namespaces[i];

    for (int i = 1; i < ns_length; i += 2)
        if(URI && state->root.namespaces[i] && strcmp((const char *)state->root.namespaces[i], (const char *)URI) == 0)
            URI = state->root.namespaces[i];

    if(state->parse_function && (strcmp((const char *)localname, "function_decl") == 0 || strcmp((const char *)localname, "function") == 0)) {

        state->in_function_header = true;
        state->current_function = function_prototype(strcmp((const char *)localname, "function_decl") == 0);

    } else if(!state->in_function_header) {

        if(state->context->handler->start_element)
            state->context->handler->start_element(state->context, (const char *)localname, (const char *)prefix, (const char *)URI,
                nb_namespaces, srcsax_namespaces, nb_attributes, srcsax_attributes);

    } else {

        if(state->current_function.mode == function_prototype::NAME && strcmp((const char *)localname, "parameter_list") == 0) {

            state->current_function.mode = function_prototype::PARAMETER_LIST;

        } else if(state->current_function.mode == function_prototype::PARAMETER_LIST && strcmp((const char *)localname, "param") == 0) {

            state->current_function.parameter_list.push_back(declaration());
            state->current_function.mode = function_prototype::PARAMETER;

        } else if(state->current_function.mode == function_prototype::PARAMETER && strcmp((const char *)localname, "init") == 0) {

            state->current_function.parameter_list.back().mode = declaration::INIT;

            state->current_function.mode = function_prototype::PARAMETER_LIST;

        }

    }

    free_srcsax_namespaces(nb_namespaces, srcsax_namespaces);
    free_srcsax_attributes(nb_attributes, srcsax_attributes);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

}

/**
 * end_element_ns
 * @param ctx an xmlParserCtxtPtr
 * @param localname the name of the element tag
 * @param prefix the tag prefix
 * @param URI the namespace of tag
 *
 * SAX handler function for end of an element.
 * Detects end of unit and calls correct functions
 * for either end_root end_unit or end_element_ns.
 */
void end_element_ns(void * ctx, const xmlChar * localname, const xmlChar * prefix, const xmlChar * URI) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

    if(ctx == NULL) return;

    if(strcmp((const char *)localname, "macro-list") == 0) {

        return;

    }    

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;  

    if(strcmp((const char *)localname, "unit") == 0) {

        if(state->mode == ROOT) {

            state->is_archive = false;
            state->context->is_archive = state->is_archive;

            if(state->context->terminate) return;

            srcsax_namespace * srcsax_namespaces_root = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(state->root.nb_namespaces, state->root.namespaces);
            srcsax_attribute * srcsax_attributes_root = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(state->root.nb_attributes, state->root.attributes);            

            if(state->context->handler->start_root)
                state->context->handler->start_root(state->context, (const char *)state->root.localname, (const char *)state->root.prefix, (const char *)state->root.URI,
                                                    state->root.nb_namespaces, srcsax_namespaces_root, state->root.nb_attributes,
                                                    srcsax_attributes_root);

            if(state->context->terminate) return;

            if(state->context->handler->meta_tag && !state->meta_tags.empty()) {

                for(std::vector<srcml_element>::const_iterator citr = state->meta_tags.begin(); citr < state->meta_tags.end(); ++citr) {

                    srcml_element_stack_push(state->context, state->srcml_element_stack, (const char *)citr->prefix, (const char *)citr->localname);

                    srcsax_namespace * srcsax_namespaces_meta_tag = (srcsax_namespace *)libxml2_namespaces2srcsax_namespaces(citr->nb_namespaces, citr->namespaces);
                    srcsax_attribute * srcsax_attributes_meta_tag = (srcsax_attribute *)libxml2_attributes2srcsax_attributes(citr->nb_attributes, citr->attributes);  

                    if(state->context->terminate) {

                        free_srcsax_namespaces(state->root.nb_namespaces, srcsax_namespaces_root);
                        free_srcsax_attributes(state->root.nb_attributes, srcsax_attributes_root);
                        return;

                    }

                    state->context->handler->meta_tag(state->context, (const char *)citr->localname, (const char *)citr->prefix, (const char *)citr->URI,
                                                        citr->nb_namespaces, srcsax_namespaces_meta_tag, citr->nb_attributes,
                                                        srcsax_attributes_meta_tag);

                    free_srcsax_namespaces(citr->nb_namespaces, srcsax_namespaces_meta_tag);
                    free_srcsax_attributes(citr->nb_attributes, srcsax_attributes_meta_tag);

                    srcml_element_stack_pop(state->context, state->srcml_element_stack);

                }

            }

            if(state->context->terminate) {

                free_srcsax_namespaces(state->root.nb_namespaces, srcsax_namespaces_root);
                free_srcsax_attributes(state->root.nb_attributes, srcsax_attributes_root);
                return;

            }

            if(state->context->handler->start_unit)
                state->context->handler->start_unit(state->context, (const char *)state->root.localname, (const char *)state->root.prefix, (const char *)state->root.URI,
                                                    state->root.nb_namespaces, srcsax_namespaces_root, state->root.nb_attributes,
                                                    srcsax_attributes_root);

            free_srcsax_namespaces(state->root.nb_namespaces, srcsax_namespaces_root);
            free_srcsax_attributes(state->root.nb_attributes, srcsax_attributes_root);

            if(state->context->terminate) return;

            if(state->characters.size() != 0 && state->context->handler->characters_unit)
                state->context->handler->characters_unit(state->context, state->characters.c_str(), (int)state->characters.size());

        }

        srcml_element_stack_pop(state->context, state->srcml_element_stack);  

        if(state->context->terminate) return;

        if(ctxt->sax->startElementNs == &start_unit) {

            state->mode = END_ROOT;
            if(state->context->handler->end_root)
                state->context->handler->end_root(state->context, (const char *)localname, (const char *)prefix, (const char *)URI);

        } else {

            state->mode = END_UNIT;
            if(state->context->handler->end_unit)
                state->context->handler->end_unit(state->context, (const char *)localname, (const char *)prefix, (const char *)URI);
            if(ctxt->sax->startElementNs) ctxt->sax->startElementNs = &start_unit;
            if(ctxt->sax->characters) {

                ctxt->sax->characters = &characters_root;
                ctxt->sax->ignorableWhitespace = &characters_root;

            }
        }

        if(state->context->terminate) return;

    } else {

        srcml_element_stack_pop(state->context, state->srcml_element_stack);  

        if(state->in_function_header && (strcmp((const char *)localname, "function_decl") == 0 || strcmp((const char *)localname, "function") == 0)) {

            //state->context->handler->endFunction();

        } else if(!state->in_function_header) {

            if(state->context->terminate) return;

            if(state->context->handler->end_element)
                state->context->handler->end_element(state->context, (const char *)localname, (const char *)prefix, (const char *)URI);

            if(state->context->terminate) return;

        } else {

            if(state->current_function.mode == function_prototype::RETURN_TYPE && strcmp((const char *)localname, "type") == 0) {

                state->current_function.mode = function_prototype::NAME;

            } else if(state->current_function.mode == function_prototype::PARAMETER && state->current_function.parameter_list.back().mode == declaration::TYPE
                    && strcmp((const char *)localname, "type") == 0) {

                state->current_function.parameter_list.back().mode = declaration::NAME;

            } else if(state->current_function.mode == function_prototype::PARAMETER 
                && (strcmp((const char *)localname, "param") == 0 || strcmp((const char *)localname, "decl") == 0)) {

                state->current_function.mode = function_prototype::PARAMETER_LIST;

            } else if(state->current_function.mode == function_prototype::PARAMETER_LIST && strcmp((const char *)localname, "parameter_list") == 0) {

                state->in_function_header = false;
                //state->context->handler->startFunction(state->current_function.name, state->current_function.return_type, state->current_function.parameter_list, state->current_function.is_decl);

            }

        }

    }

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, (const char *)localname);
#endif

}

/**
 * characters_first
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling before we
 * know if we have an archive or not.
 * Immediately calls supplied handlers function.
 */
void characters_first(void * ctx, const xmlChar * ch, int len) {

#ifdef SRCSAX_DEBUG
    std::string chars;
    chars.append((const char *)ch, len);
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    state->characters.append((const char *)ch, len);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

}

/**
 * characters_root
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling at the root level.
 * Immediately calls supplied handlers function.
 */
void characters_root(void * ctx, const xmlChar * ch, int len) {

#ifdef SRCSAX_DEBUG
    std::string chars;
    chars.append((const char *)ch, len);
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    if(state->context->terminate) return;

    if(state->context->handler->characters_root)
        state->context->handler->characters_root(state->context, (const char *)ch, len);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

}

/**
 * characters_unit
 * @param ctx an xmlParserCtxtPtr
 * @param ch the characers
 * @param len number of characters
 *
 * SAX handler function for character handling within a unit.
 * Immediately calls supplied handlers function.
 */
void characters_unit(void * ctx, const xmlChar * ch, int len) {

#ifdef SRCSAX_DEBUG
    std::string chars;
    chars.append((const char *)ch, len);
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;


    if(!state->in_function_header) {

        if(state->context->terminate) return;

        if(state->context->handler->characters_unit)
            state->context->handler->characters_unit(state->context, (const char *)ch, len);

    } else {

        if(state->current_function.mode == function_prototype::RETURN_TYPE)
            state->current_function.return_type.append((const char *)ch, len);
        else if(state->current_function.mode == function_prototype::NAME)
            state->current_function.name.append((const char *)ch, len);
        else if(state->current_function.mode == function_prototype::PARAMETER) {

            if(state->current_function.parameter_list.back().mode == declaration::TYPE)
                state->current_function.parameter_list.back().type.append((const char *)ch, len);
            else if(state->current_function.parameter_list.back().mode == declaration::NAME)
                state->current_function.parameter_list.back().name.append((const char *)ch, len);

        }

    }

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d '%s'\n", __FILE__, __FUNCTION__, __LINE__, chars.c_str());
#endif

}

/**
 * comment
 * @param ctx an xmlParserCtxtPtr
 * @param value the comment content
 *
 * A comment has been parsed.
 * Immediately calls supplied handlers function.
 */
void comment(void * ctx, const xmlChar * value) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    if(state->context->terminate) return;

    if(state->context->handler->comment)
        state->context->handler->comment(state->context, (const char *)value);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

}

/**
 * cdata_block
 * @param ctx an xmlParserCtxtPtr
 * @param value the pcdata content
 * @param len the block length
 *
 * Called when a pcdata block has been parsed.
 * Immediately calls supplied handlers function.
 */
void cdata_block(void * ctx, const xmlChar * value, int len) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    if(state->context->terminate) return;

    if(state->context->handler->cdata_block)
        state->context->handler->cdata_block(state->context, (const char *)value, len);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

}

/**
 * processing_instruction
 * @param ctx an xmlParserCtxtPtr
 * @param target the processing instruction target.
 * @param data the processing instruction data.
 *
 * Called when a processing instruction has been parsed.
 * Immediately calls supplied handlers function.
 */
void processing_instruction(void * ctx, const xmlChar * target, const xmlChar * data) {

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

    if(ctx == NULL) return;

    xmlParserCtxtPtr ctxt = (xmlParserCtxtPtr) ctx;
    sax2_srcsax_handler * state = (sax2_srcsax_handler *) ctxt->_private;

    if(state->context->terminate) return;

    if(state->context->handler->processing_instruction)
        state->context->handler->processing_instruction(state->context, (const char *)target, (const char *)data);

#ifdef SRCSAX_DEBUG
    fprintf(stderr, "HERE: %s %s %d\n", __FILE__, __FUNCTION__, __LINE__);
#endif

}

#pragma GCC diagnostic pop
