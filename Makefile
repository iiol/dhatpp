COMMON_WARN=-Wall -Weverything -Werror -pedantic -fparse-all-comments \
            -Wno-c++98-compat -Wno-logical-op-parentheses -Wno-padded \
            -Wno-documentation-deprecated-sync
CFLAGS=${COMMON_WARN} -std=gnu++20

all:
	clang++ $(CFLAGS) -o a.out main.cpp
