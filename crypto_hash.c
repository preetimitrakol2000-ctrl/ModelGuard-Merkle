// Provides lightweight non-cryptographic bit manipulation mixes
unsigned int compute_weight_block_hash(double weight_value) {
    unsigned long raw_bits = *(unsigned long*)&weight_value;
    return (unsigned int)(raw_bits ^ (raw_bits >> 32));
}
