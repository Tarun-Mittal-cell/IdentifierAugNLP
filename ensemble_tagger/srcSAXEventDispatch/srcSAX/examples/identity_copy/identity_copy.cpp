/**
 * @file identity_copy.hpp
 *
 * @copyright Copyright (C) 2013-2014  SDML (www.srcML.org)
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
 * Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
 */

 /*

  Copy the srcML document.

  Input: input_file.xml
  Input: output_file.xml
  Useage: identity_copy input_file.xml output_file.xml
  
  */

#include "identity_copy_handler.hpp"
#include <srcSAXController.hpp>

#include <iostream>

/**
 * main
 * @param argc number of arguments
 * @param argv the provided arguments (array of C strings)
 * 
 * Invoke srcSAX handler to copy the supplied srcML document and into the given
 * output file.
 */
 int main(int argc, char * argv[]) {

  if(argc < 3) {

    std::cerr << "Useage: identify_copy input_file.xml output_file.xml\n";
    exit(1);

  }

  srcSAXController control(argv[1]);
  identity_copy_handler handler(argv[2]);
  control.parse(&handler);

  return 0;
}
