import os
import xml.etree.ElementTree as ET
import subprocess
import requests
import json
import tempfile

def implements_action_listener(class_element, ns):
    implements_tags = class_element.findall('.//src:implements', namespaces=ns)
    for implements_tag in implements_tags:
        for name_tag in implements_tag.findall('.//src:name', namespaces=ns):
            print(f"Implements: {name_tag.text}")
            if name_tag.text == 'ActionListener':
                return True
    return False

def extract_event_driven_snippets(class_element, ns):
    snippets = []
    for method_element in class_element.findall('./src:block/src:method', namespaces=ns):
        snippet = ET.tostring(method_element, encoding='unicode', method='xml')
        snippets.append(snippet)
        print("Snippet:")
        print(snippet)
    return snippets

def get_pos_tags(identifier_type, identifier_name, code_context):
    response = requests.get(f"http://127.0.0.1:5000/{identifier_type}/{identifier_name}/{code_context}")

    if response.status_code == 200:
        return json.loads(response.text)
    else:
        print("Failed to get POS tags")
        return None


def run_code2vec(code_snippet):
    with tempfile.NamedTemporaryFile(mode="w+", delete=False) as temp_file:
        temp_file.write(code_snippet)
        temp_file_name = temp_file.name

    print(f"Temporary file created: {temp_file_name}")

    code2vec_command = [
        "python3",
        "/Users/tarunmittal/Desktop/NLP Project/code2vec/code2vec.py",
        "--load",
        "/Users/tarunmittal/Desktop/NLP Project/code2vec/models/java14_model/saved_model_iter8.release",
        "--file",
        temp_file_name,
    ]

    proc = subprocess.run(code2vec_command, capture_output=True, text=True)
    os.remove(temp_file_name)  

    print(f"code2vec stdout: {proc.stdout}")
    print(f"code2vec stderr: {proc.stderr}")

    if proc.returncode != 0:
        print(f"code2vec error: {proc.stderr}")
        return []
    else:
        identifier_names = proc.stdout.strip().split("\n")[1:]
        return identifier_names


        
def run_java_best_match(identifier_name):
    compile_java = subprocess.run(["javac", "-cp", "/Users/tarunmittal/Desktop/NLP Project/Expand", "Main.java"], text=True)
    if compile_java.returncode != 0:
        print("Failed to compile Java code")
        return None

    run_java = subprocess.run(["java", "-cp", "/Users/tarunmittal/Desktop/NLP Project/Expand", "Main", identifier_name], capture_output=True, text=True)
    if run_java.returncode != 0:
        print("Failed to run Java code")
        return None

    return run_java.stdout.strip()

ns = {'src': 'http://www.srcML.org/srcML/src'}

event_driven_code_examples = [
    os.path.join("/Users/tarunmittal/Desktop/NLP Project/Event Driven Code Examples", "Example1.xml"),
    os.path.join("/Users/tarunmittal/Desktop/NLP Project/Event Driven Code Examples", "Example2.xml"),
    os.path.join("/Users/tarunmittal/Desktop/NLP Project/Event Driven Code Examples", "Example3.xml")
]

for example_path in event_driven_code_examples:
    tree = ET.parse(example_path)
    root = tree.getroot()

    for class_element in root.findall('./src:class', namespaces=ns):
        if implements_action_listener(class_element, ns):
            print(f"{example_path} contains event-driven code!")
            snippets = extract_event_driven_snippets(class_element, ns)
            for snippet in snippets:
                print("Running code2vec...")
                code2vec_output = run_code2vec(snippet)
                print(f"code2vec output for {example_path}:")
                print(code2vec_output)

                prepositions = ["of", "in", "on"]
                potential_names = []
                for identifier_name in code2vec_output:
                    pos_tags = get_pos_tags("int", identifier_name, "FUNCTION")
                    if pos_tags:
                        potential_names.append(identifier_name)

                print("Potential names containing prepositions:")
                print(potential_names)

                # Run Java code for each identifier and get the best match
                for identifier_name in potential_names:
                    best_match = run_java_best_match(identifier_name)
                    if best_match:
                        print(f"Best match for '{identifier_name}' is: {best_match}")
                    else:
                        print(f"Failed to get best match for '{identifier_name}'")

        else:
            print(f"{example_path} does not contain event-driven code!")
