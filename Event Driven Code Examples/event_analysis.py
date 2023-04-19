import os
import xml.etree.ElementTree as ET
import subprocess
import requests
import json

def implements_action_listener(class_element):
    implements_tag = class_element.find('./src:super_list/src:implements', namespaces=ns)
    if implements_tag is not None:
        for name_tag in implements_tag.findall('.//src:name', namespaces=ns):
            if name_tag.text == 'ActionListener':
                return True
    return False

ns = {'src': 'http://www.srcML.org/srcML/src'}

code2vec_path = "../code2vec"

def get_pos_tags(identifier_type, identifier_name, prepositions):
    url = f"http://localhost:5001/{identifier_type}/{identifier_name}/FUNCTION"
    response = requests.get(url)
    pos_tags = json.loads(response.text)
    return {word: tag for word, tag in pos_tags.items() if tag in prepositions}

for filename in os.listdir('.'):
    if filename.endswith('.xml'):
        tree = ET.parse(filename)
        root = tree.getroot()

        for class_element in root.findall('./src:class', namespaces=ns):
            if implements_action_listener(class_element):
                print(f"{filename} contains event-driven code!")

                with open("temp.java", "w") as f:
                    f.write(ET.tostring(class_element, encoding="unicode"))

                with open("temp.java", "r") as f:
                    print("Content of temp.java:")
                    print(f.read())

                with open("stdin.txt", "w") as f:
                    f.write("temp.java\n")

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

                        identifier_names = result.strip().split("\n")[1:]

                        prepositions = ["of", "in", "on"]
                        potential_names = []
                        for identifier_name in identifier_names:
                            pos_tags = get_pos_tags("int", identifier_name, prepositions)
                            if pos_tags:
                                potential_names.append(identifier_name)

                        print("Potential names containing prepositions:")
                        print(potential_names)

                os.remove("temp.java")
                os.remove("stdin.txt")

                break

            else:
                print(f"{filename} does not contain event-driven code!")
