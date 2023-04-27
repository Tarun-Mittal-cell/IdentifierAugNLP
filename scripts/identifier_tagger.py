import sys
sys.path.append('/Users/tarunmittal/Desktop/NLP Project/code2vec')
import code2vec
from ensemble_tagger import EnsembleTagger

# Replace this list with your actual code snippets
code_snippets = [
    "public void actionPerformed(ActionEvent e) { ... }",
    "public static void main(String[] args) { ... }"
]

# Load the pre-trained code2vec model
model_path = "/Users/tarunmittal/Desktop/NLP Project/code2vec/models/java14_model"
model = code2vec.Code2Vec.load(model_path)

# Load the ensemble tagger
tagger = EnsembleTagger()

# Process code snippets and predict identifier names
predicted_identifiers = []

for snippet in code_snippets:
    prediction = model.predict(snippet, top_k=1)
    if prediction:
        predicted_identifiers.append(prediction[0].name)

# Feed the predicted identifier names to the ensemble tagger
tagged_identifiers = []

for identifier in predicted_identifiers:
    pos_tags = tagger.tag(identifier)
    tagged_identifiers.append((identifier, pos_tags))

# Print the tagged identifiers
for identifier, pos_tags in tagged_identifiers:
    print(f"Identifier: {identifier} | POS Tags: {pos_tags}")
