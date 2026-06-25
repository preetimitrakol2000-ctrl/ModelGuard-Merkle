# ModelGuard-Merkle

A pure C99 model verification engine designed to detect unauthorized modifications in edge neural networks. By organizing serialized neural weight matrices into a custom **Merkle Tree**, this architecture provides tamper-evidence profiling for security-focused AI systems.

## 🧮 Cryptographic & DSA Properties
* **Data Structure:** Full Binary Merkle Tree with bottom-up hash propagation.
* **Verification Complexity:** Logarithmic $O(\log N)$ structural audit proofs.
* **Space Overhead:** Lean contiguous leaf tracking array avoiding external crypto overhead.

## 📦 Compilation & Execution
```bash
gcc main.c merkle_tree.c crypto_hash.c -o model_guard -lm
./model_guard
