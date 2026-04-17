# Minishell Interfaces

## Interface 1 -- Lexer Output / Parser Input

### Token types

    #define WORD          0
    #define PIPE          1
    #define REDIR_IN      2
    #define REDIR_OUT     3
    #define HEREDOC       4
    #define REDIR_APPEND  5

### Quote types (for segments)

    #define S_QUOTED  0
    #define D_QUOTED  1
    #define UNQUOTED  2

### Structs

    typedef struct s_segment
    {
        char              *value;
        int               quote_type;
        struct s_segment  *next;
    } t_segment;

    typedef struct s_token
    {
        int              type;
        t_segment        *segments;
        struct s_token   *before;
        struct s_token   *next;
    } t_token;

### Example: echo "$USER"'!'

    Token 1                              Token 2
    +----------------+                   +----------------+
    | type: WORD     |    next           | type: WORD     |
    | segments:      +------------------>| segments:      |
    | before: NULL   |<------------------+ before:        |
    | next:          |    before         | next: NULL     |
    +-------+--------+                   +--------+-------+
            |                                     |
            v                                     v
    +--------------+               +---------------+   +--------------+
    | val: "echo"  |               | val: "$USER"  |   | val: "!"     |
    | qt: UNQUOTED |               | qt: D_QUOTED  |   | qt: S_QUOTED |
    | next: NULL   |               | next: --------|-->| next: NULL   |
    +--------------+               +---------------+   +--------------+

### Example: ls -l > out.txt | wc

       Token 1    Token 2    Token 3        Token 4       Token 5    Token 6
       +------+   +------+   +---------+   +----------+   +------+   +------+
NULL<--| WORD |-->| WORD |-->|REDIR_OUT|-->| WORD     |-->| PIPE |-->| WORD |-->NULL
       | "ls" |<--| "-l" |<--| ">"     |<--| "out.txt"|<--| "|"  |<--| "wc" |
       +------+   +------+   +---------+   +----------+   +------+   +------+

---

## Interface 2 -- Expander Output / Executor Input

### Structure

Binary tree. One struct for all nodes:

    typedef struct s_redir
    {
        int             type;
        char            *file;
        struct s_redir  *next;
    } t_redir;

    typedef struct s_tree
    {
        int             type;
        char            **argv;
        t_redir         *redirections;
        struct s_tree   *left;
        struct s_tree   *right;
    } t_tree;

- PIPE node: uses type, left, right. argv and redirections are NULL.
- CMD node: uses type, argv, redirections. left and right are NULL.

Redirection type reuses REDIR_IN, REDIR_OUT, HEREDOC, REDIR_APPEND.

### Example: cat -e < in.txt | grep hello > out.txt

                    +---------------------------+
                    | type: PIPE                |
                    | argv: NULL                |
                    | redirs: NULL              |
                    | left:        right:       |
                    +----+--------------+-------+
                         |              |
              +----------v---+   +------v-----------+
              | type: CMD    |   | type: CMD         |
              | argv:        |   | argv:             |
              | ["cat","-e"] |   | ["grep","hello"]  |
              | redirs:      |   | redirs:           |
              | left: NULL   |   | left: NULL        |
              | right: NULL  |   | right: NULL       |
              +-------+------+   +--------+----------+
                      |                    |
               +------v------+   +---------v-------+
               | REDIR_IN    |   | REDIR_OUT       |
               | "in.txt"    |   | "out.txt"       |
               | next: NULL  |   | next: NULL      |
               +-------------+   +-----------------+

### Example: echo hello (no pipes, no redirections)

            +----------------------+
            | type: CMD            |
            | argv: ["echo","hello"]|
            | redirs: NULL         |
            | left: NULL           |
            | right: NULL          |
            +----------------------+

Just a single CMD node. The tree still works -- it's a tree with one node.

---