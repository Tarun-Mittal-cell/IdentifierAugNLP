import os
import xml.etree.ElementTree as ET

# specify the directory containing the XML files
xml_dir = '/Users/tarunmittal/Desktop/NLP Project/Event Driven Code Examples'

# loop through all XML files in the directory
for filename in os.listdir(xml_dir):
    if not filename.endswith('.xml'):
        continue
    
    # load the XML file and print out its structure
    filepath = os.path.join(xml_dir, filename)
    tree = ET.parse(filepath)
    root = tree.getroot()
    
    print(ET.tostring(root, encoding='unicode', method='xml'))
