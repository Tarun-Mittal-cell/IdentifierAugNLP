import os
import xml.etree.ElementTree as ET
import subprocess

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

# Set the path to your code2vec repository
code2vec_path = "../code2vec"

# Print the current working directory
print("Current working directory:", os.getcwd())

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
                
                # Save the detected code to a temporary file
                with open("temp.java", "w") as f:
                    f.write(ET.tostring(class_element, encoding="unicode"))

                # Print the content of temp.java
                with open("temp.java", "r") as f:
                    print("Content of temp.java:")
                    print(f.read())

                # Write the temporary file name to a separate stdin file
                with open("stdin.txt", "w") as f:
                    f.write("temp.java\n")

                # Run code2vec using the separate stdin file
                with subprocess.Popen(
                    ["python", f"{code2vec_path}/interactive_predict.py", f"{code2vec_path}/models/java14_model/saved_model_iter8.release"],
                    stdin=open("stdin.txt", "r"), stdout=subprocess.PIPE, stderr=subprocess.PIPE, text=True
                ) as proc:
                    result, error = proc.communicate()
                    if proc.returncode != 0:
                        print(f"code2vec error: {error}")
                    else:
                        print("code2vec response:")
                        print(result)

                # Remove the temporary files
                os.remove("temp.java")
                os.remove("stdin.txt")

                break

