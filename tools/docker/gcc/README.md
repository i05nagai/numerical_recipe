## Dockerfiles for debugging gcc-4.9/g++-4.9
Build docker images.

```
docker build -t recipe/gcc:4.9 .
```

Run docker container

```
docker run \
    --rm \
    -it \
    --volume ${PATH_TO_REPOSITORY}:/tmp/repository \
    --workdir /tmp/repository \
    /bin/bash
```
