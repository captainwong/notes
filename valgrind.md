# valgrind notes

## check memory leaks

```
valgrind --leak-check=full \
         --show-leak-kinds=all \
         --track-origins=yes \
         --verbose \
         --log-file=valgrind-out.txt \
         ./executable exampleParam1
```

### reference

[How do I use valgrind to find memory leaks?](https://stackoverflow.com/a/44989219)