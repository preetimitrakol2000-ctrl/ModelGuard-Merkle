#include <stdio.h>
#include "merkle_tree.h"

extern unsigned int compute_weight_block_hash(double weight_value);

int main() {
    printf("🛡️  Activating ModelGuard-Merkle Secure Weights Engine...\n\n");

    // Simulating four model parameters
    double layer_weights[4] = {0.852, -1.421, 0.005, 3.141};
    unsigned int leaf_hashes[4];

    for (int i = 0; i < 4; i++) {
        leaf_hashes[i] = compute_weight_block_hash(layer_weights[i]);
    }

    MerkleNode* integrity_root = build_merkle_root(leaf_hashes, 4);
    unsigned int saved_secure_signature = integrity_root->combined_hash;

    printf("📥 Neural Layers Hashed. Secure Merkle Root Signature: %u\n", saved_secure_signature);

    // Audit scenario A: Unmodified evaluation pass
    printf("🔍 Audit Pass A (Unmodified File System): %s\n", 
           verify_tree_integrity(integrity_root, secure_signature) ? "✅ INTEGRITY PASS" : "🚨 TAMPERING DETECTED");

    // Simulate an adversarial memory payload swap injection
    layer_weights[1] = -1.420; // Altering weights slightly
    leaf_hashes[1] = compute_weight_block_hash(layer_weights[1]);
    MerkleNode* tainted_root = build_merkle_root(leaf_hashes, 4);

    printf("🔍 Audit Pass B (Adversarial Alteration Active): %s\n", 
           verify_tree_integrity(tainted_root, secure_signature) ? "✅ INTEGRITY PASS" : "🚨 SYSTEM FRAUD BLOCK (TAMPERING DETECTED)");

    clear_merkle_tree(integrity_root);
    clear_merkle_tree(tainted_root);
    return 0;
}
