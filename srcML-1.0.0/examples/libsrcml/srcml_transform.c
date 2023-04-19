/**
 * @file srcml_transform.c
 *
 * @copyright Copyright (C) 2013-2019 srcML, LLC. (www.srcML.org)
 *
 * The srcML Toolkit is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 2 of the License, or
 * (at your option) any later version.
 *
 * The srcML Toolkit is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with the srcML Toolkit; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

/*
  Example program of the use of the C API for srcML.

  Use XPath, XSLT, and RelaxNG.
*/

#include <srcml.h>

int main(int argc, char * argv[]) {

    struct srcml_archive* iarchive = srcml_archive_create();
    srcml_archive_read_open_filename(iarchive, "project.xml");
    struct srcml_archive* oarchive = srcml_archive_clone(iarchive);
    srcml_archive_write_open_filename(oarchive, "transform.xml");

    srcml_append_transform_xpath(iarchive, "//src:unit");
    srcml_append_transform_xslt_filename(iarchive, "copy.xsl");
    srcml_append_transform_relaxng_filename(iarchive, "schema.rng");
/*
    srcml_apply_transforms(iarchive, oarchive);
*/
    srcml_archive_close(iarchive);
    srcml_archive_close(oarchive);

    srcml_archive_free(iarchive);
    srcml_archive_free(oarchive);

    return 0;
}
