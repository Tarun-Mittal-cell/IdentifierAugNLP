import os
import xml.etree.ElementTree as ET

# Function to check if a class implements ActionListener interface
def implements_action_listener(class_element):
    # Look for 'implements' tag
    implements_tag = class_element.find('./src:super_list/src:implements', namespaces=ns)
    if implements_tag is not None:
        # Look for ActionListener interface
        for name_tag in implements_tag.findall('.//src:name', namespaces=ns):
            if name_tag.text == 'ActionListener':
                return True
    return False

# Define namespace for srcML
ns = {'src': 'http://www.srcML.org/srcML/src'}

# Loop through all XML files in directory
for filename in os.listdir('.'):
    if filename.endswith('.xml'):
        # Parse XML file
        tree = ET.parse(filename)
        root = tree.getroot()

        # Look for 'class' tags
        for class_element in root.findall('./src:class', namespaces=ns):
            # Check if class implements ActionListener
            if implements_action_listener(class_element):
                print(f"{filename} contains event-driven code!")
                break
