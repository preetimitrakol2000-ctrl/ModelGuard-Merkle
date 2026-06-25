#ifndef MERKLE_TREE_H
#define MERKLE_TREE_H

typedef struct MerkleNode {
    unsigned int combined_hash;
    struct MerkleNode* left_child;
    struct MerkleNode* right_child;
} MerkleNode;

MerkleNode* build_merkle_root(unsigned int* initial_hashes, int leaf_count);
int verify_tree_integrity(MerkleNode* root, unsigned int expected_root_hash);
void clear_merkle_tree(MerkleNode* root);

#endif
