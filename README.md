# Prieto-Peña Trees: Recursive Generation of Pythagorean n-tuples

**Author**: Ernesto H. Prieto Peña, ESE-IPN 1973-1978  
**Original idea**: October 2006 [Internet Archive](https://archive.org/details/diophantine_202309)  
**Formal version**: April 2026 DOI: [10.5281/zenodo.19596333](https://doi.org/10.5281/zenodo.19596333)

## Method
Recursive algorithm to generate integer solutions for $x_1^2 + ... + x_n^2 = z^2$. 
For prime seed $x_1 = p$, each choice of square factor $p_k$ yields primitive trees.

Core formula: $Y = \frac{x^2 - p_n}{2\sqrt{p_n}}$,  $Z = \frac{x^2 + p_n}{2\sqrt{p_n}}$

## Potential Applications
1. **Game Dev / Graphics**: Integer-only voxel distances. Remove `sqrt()` in shaders/physics.
2. **Software Testing**: Generate exact-norm test vectors for linear algebra libraries.
3. **Lattice Cryptography**: Construct witnesses for zero-knowledge proofs over sum-of-squares.
4. **Spatial Databases**: Exact-metric indexes in PostGIS without floating-point error.
5. **Telecom**: n-dimensional QAM constellations with integer energy.

## Citation
If you use this work in research or product, please cite:  
Prieto Peña, E. H. (2026). *Symmetric Solution to n-tuples in Indeterminate Diophantine  Equations. Method of Generating Pythagorean n-tuples*. Zenodo. https://doi.org/10.5281/zenodo.19596333

## License
MIT License. Acknowledgment appreciated but not required.
