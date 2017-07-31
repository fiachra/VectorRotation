# Vector Rotation Tests

This is a simple C project to test out 3D Vector Rotations. To try to keep everything self contained a number of linear algebra
code snippets have been used from around the web. Proper attributions will be included if not already. In other circumstances to avoid the many possible errors this approach might throw up, proper linear algebra libraries (CLAPACK, LAPACK, BLAS) should be used.

This system currently converts an object's world position to a local position defined by a listener object's location and orientation. It does this by composing the translation and 3 rotation matrices for the listener object and generation a single transformation matrix. Getting the inverse of this transformation matrix and multiplying by the objects position converts that from world to local.

An improved approach would use Quaternions to reduce computation and negate the singularities (Gimbal Lock) possible with this approach.         

## Getting Started

Clone this repo and use gcc or Make to compile.

```bash
# Clone this repository
$ git clone https://github.com/fiachra/VectorRotation.git

# Go into the repository
$ cd VectorRotation

# Compile with gcc
$ gcc -Wall test.c VectorRotation.c Utilities.c Quaternion.c -o VectorRotation

# Or Simply Make
$ make

# run the app
$ ./VectroRotation
```

This will run a series of tests in the test.c

## Next Steps / To Dos

* Include tests for failure conditions
* add all necessary attributions
* Implement quaternion approach


## Author

* **Fiachra Matthews** [Github Page](https://github.com/fiachra)
