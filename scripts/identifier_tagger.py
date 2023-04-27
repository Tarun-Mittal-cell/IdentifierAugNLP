import sys
import requests
sys.path.append('/Users/tarunmittal/Desktop/NLP Project/code2vec')

import code2vec

# Replace this list with your actual code snippets
code_snippets = [
    "public void actionPerformed(ActionEvent e) { ... }",
    "public static void main(String[] args) { ... }"
]

# Load the pre-trained code2vec model
model_path = "/Users/tarunmittal/Desktop/NLP Project/code2vec/models/java14_model"
model = code2vec.Code2Vec.load(model_path)

# Process code snippets and predict identifier names
predicted_identifiers = []

for snippet in code_snippets:
    prediction = model.predict(snippet, top_k=1)
    if prediction:
        predicted_identifiers.append(prediction[0].name)

# Send the predicted identifier names to the ensemble tagger server
ensemble_tagger_server_url = "http://127.0.0.1:5003"
tagged_identifiers = []

for identifier in predicted_identifiers:
    # Update the identifier_type and code_context based on your specific use case
    identifier_type = "int"
    code_context = "DECLARATION"
    request_url = f"{ensemble_tagger_server_url}/{identifier_type}/{identifier}/{code_context}"
    response = requests.get(request_url)

    if response.status_code == 200:
        pos_tags = response.json()
        tagged_identifiers.append((identifier, pos_tags))
    else:
        print(f"Error while processing identifier: {identifier}")

# Print the tagged identifiers
for identifier, pos_tags in tagged_identifiers:
    print(f"Identifier: {identifier} | POS Tags: {pos_tags}")
