#include <stdlib.h>
#include "merkle_tree.h"

MerkleNode* build_merkle_root(unsigned int* initial_hashes, int leaf_count) {
    if (leaf_count <= 0) return NULL;

    // Dynamically prepare the base layer of nodes (leaves)
    MerkleNode** current_layer = (MerkleNode**)malloc(leaf_count * sizeof(MerkleNode*));
    for (int i = 0; i < leaf_count; i++) {
        current_layer[i] = (MerkleNode*)malloc(sizeof(MerkleNode));
        current_layer[i]->combined_hash = initial_hashes[i];
        current_layer[i]->left_child = NULL;
        current_layer[i]->right_child = NULL;
    }

    // Pair nodes bottom-up until a single root remains
    while (leaf_count > 1) {
        int next_layer_count = (leaf_count + 1) / 2;
        MerkleNode** next_layer = (MerkleNode**)malloc(next_layer_count * sizeof(MerkleNode*));

        for (int i = 0; i < leaf_count; i += 2) {
            MerkleNode* parent = (MerkleNode*)malloc(sizeof(MerkleNode));
            parent->left_child = current_layer[i];
            
            if (i + 1 < leaf_count) {
                parent->right_child = current_layer[i + 1];
                // Deterministic non-overflowing hash combination formula
                parent->combined_hash = (current_layer[i]->combined_hash ^ current_layer[i + 1]->combined_hash) * 16777619;
            } else {
                parent->right_child = NULL;
                parent->combined_hash = current_layer[i]->combined_hash;
            }
            next_layer[i / 2] = parent;
        }
        free(current_layer);
        current_layer = next_layer;
        leaf_count = next_layer_count;
    }

    MerkleNode* final_root = current_layer[0];
    free(current_layer);
    return final_root;
}

int verify_tree_integrity(MerkleNode* root, unsigned int expected_root_hash) {
    if (!root) return 0;
    return root->combined_hash == expected_root_hash;
}

void clear_merkle_tree(MerkleNode* root) {
    if (!root) return;
    clear_merkle_tree(root->left_child);
    clear_merkle_tree(root->right_child);
    free(root);
}
