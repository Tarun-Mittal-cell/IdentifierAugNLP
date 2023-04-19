import os
import xml.etree.ElementTree as ET
import subprocess
import requests
import json

def implements_action_listener(class_element, ns):
    implements_tag = class_element.find('./src:super_list/src:implements', namespaces=ns)
    if implements_tag is not None:
        for name_tag in implements_tag.findall('.//src:name', namespaces=ns):
            if name_tag.text == 'ActionListener':
                return True
    return False

def extract_event_driven_snippets(class_element, ns):
    snippets = []
    for method_element in class_element.findall('./src:method/src:block', namespaces=ns):
        snippet = ET.tostring(method_element, encoding='unicode', method='xml')
        snippets.append(snippet)
    return snippets

def get_pos_tags(identifier_type, identifier_name, prepositions):
    url = f"http://localhost:5003/{identifier_type}/{identifier_name}/FUNCTION"
    response = requests.get(url)
    pos_tags = json.loads(response.text)
    return {word: tag for word, tag in pos_tags.items() if tag in prepositions}

def run_code2vec(code_snippet):
    with subprocess.Popen(
        ["python", "../code2vec/interactive_predict.py", "../code2vec/models/java14_model/saved_model_iter8.release"],
        stdin=subprocess.PIPE, stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
    ) as proc:
        result, error = proc.communicate(code_snippet)
        if proc.returncode != 0:
            print(f"code2vec error: {error}")
            return []
        else:
            identifier_names = result.strip().split("\n")[1:]
            return identifier_names

ns = {'src': 'http://www.srcML.org/srcML/src'}

event_driven_code_examples = [
    os.path.join("..", "Event Driven Code Examples", "Example1.xml"),
    os.path.join("..", "Event Driven Code Examples", "Example2.xml"),
    os.path.join("..", "Event Driven Code Examples", "Example3.xml")
]

for example_path in event_driven_code_examples:
    tree = ET.parse(example_path)
    root = tree.getroot()

    for class_element in root.findall('./src:class', namespaces=ns):
        if implements_action_listener(class_element, ns):
            print(f"{example_path} contains event-driven code!")
            snippets = extract_event_driven_snippets(class_element, ns)

            for snippet in snippets:
                code2vec_output = run_code2vec(snippet)
                print(f"code2vec output for {example_path}:")
                print(code2vec_output)

                prepositions = ["of", "in", "on"]
                potential_names = []
                for identifier_name in code2vec_output:
                    pos_tags = get_pos_tags("int", identifier_name, prepositions)
                    if pos_tags:
                        potential_names.append(identifier_name)

                print("Potential names containing prepositions:")
                print(potential_names)

        else:
            print(f"{example_path} does not contain event-driven code!")
