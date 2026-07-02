# Shell Tools for K&R C Work

A working reference for the Unix mechanics that surround compiling, running, and testing small C programs — the stuff K&R assumes you already know. Oriented toward the Chapter 1 kind of program: read stdin, loop on `getchar()` until EOF, print something.

## Contents

- [The compile-run loop](#the-compile-run-loop)
- [Where stdin comes from (the EOF problem)](#where-stdin-comes-from-the-eof-problem)
- [Capturing and inspecting output](#capturing-and-inspecting-output)
- [Seeing the bytes (matters more than you'd think)](#seeing-the-bytes-matters-more-than-youd-think)
- [Quick text tools that come up](#quick-text-tools-that-come-up)
- [Comparing your output to expected](#comparing-your-output-to-expected)
- [A realistic test cycle](#a-realistic-test-cycle)

---

## The compile-run loop

```sh
cc program.c              # produces ./a.out
./a.out                   # run it

cc -o wc program.c        # name the binary yourself
./wc

cc -Wall -Wextra program.c   # turn on warnings — do this always
```

`cc` is the system C compiler (gcc or clang depending on setup; on your Arch box it's gcc unless you've aliased it). `-Wall -Wextra` will catch a lot of the uninitialized-variable and type mistakes K&R's terse style invites. There's no reason not to leave them on.

Rebuild-and-run in one shot, so a failed compile stops before running a stale binary:

```sh
cc -Wall program.c && ./a.out
```

---

## Where stdin comes from (the EOF problem)

A K&R loop like `while ((c = getchar()) != EOF)` reads from **standard input**. By default that's your keyboard. The program isn't broken when it seems to hang — it's waiting for you to feed it input and then signal end-of-input.

**Signal EOF from the keyboard:** press `Ctrl-D` on a line by itself. That's the terminal's way of saying "input's done." One `Ctrl-D` at the start of a fresh line closes stdin; if you've typed characters on the current line without Enter, it takes two.

**Feed a file in instead** — redirect it into stdin with `<`:

```sh
./a.out < test.txt
```

Now the program reads the file's contents as if you'd typed them, hits real EOF at the end of the file automatically, and exits. This is the clean way to test the same input repeatedly instead of retyping it.

**Feed a quick literal string:**

```sh
echo "hello world" | ./a.out
printf "no trailing newline" | ./a.out
```

`echo` adds a trailing newline; `printf` gives you exact control (important when an exercise cares about whether the last line ends in `\n`). The `|` pipe connects `echo`'s output to your program's input.

**Type a multi-line block inline** with a heredoc — everything until the `EOF` marker becomes stdin:

```sh
./a.out <<'EOF'
line one
line two
EOF
```

The quotes around the first `'EOF'` stop the shell from expanding `$variables` inside the block, which is what you want for literal test data.

---

## Capturing and inspecting output

```sh
./a.out > out.txt          # write stdout to a file (overwrites)
./a.out >> out.txt         # append instead
./a.out < in.txt > out.txt # redirect both ends at once
./a.out | tee out.txt      # see it AND save it
```

`>` sends output to a file silently; `tee` splits it so you watch it scroll by *and* keep a copy. Errors go to a separate stream (stderr), so compiler warnings still print even when you redirect stdout — redirect those with `2>` if you ever need to.

---

## Seeing the bytes (matters more than you'd think)

Several Chapter 1 exercises hinge on whitespace, tabs, and newlines — characters you can't see by eye. These tools make them visible.

```sh
cat -A file.txt      # show tabs as ^I, line ends as $
od -c file.txt       # bytes as readable chars (\t, \n, spaces shown)
xxd file.txt         # hex + ascii side by side
```

`od -c` is the one to reach for when a char-counting or tab-expansion exercise gives a number you don't expect — it shows you exactly what's in the stream, including the trailing newline that `echo` slipped in or the one your editor added.

```sh
wc file.txt          # lines, words, bytes — in that order
wc -l                # lines only
wc -c                # bytes
wc -m                # characters (differs from bytes on multibyte input)
```

`wc` is effectively the reference implementation for half of Chapter 1. When you write your own line/word/char counter, `wc` is what you check your answer against:

```sh
./mycounter < test.txt
wc test.txt
```

---

## Quick text tools that come up

```sh
head -5 file        # first 5 lines
tail -5 file        # last 5 lines
grep pattern file   # lines matching a pattern
sort file           # sort lines
uniq                # collapse adjacent duplicate lines (sort first)
tr 'a-z' 'A-Z'      # translate/delete characters, stream-style
```

`tr` is worth a look precisely because it does in one line what some K&R exercises have you do in C — squeezing runs of blanks, stripping characters, case-folding. Reading its behavior can clarify what your own version is supposed to produce.

---

## Comparing your output to expected

When you've got a known-good output saved, `diff` tells you exactly where yours differs instead of you squinting at two blocks of text:

```sh
./a.out < input.txt > mine.txt
diff mine.txt expected.txt      # silent = identical; otherwise shows the deltas
```

Or skip the temp file entirely with process substitution:

```sh
diff <(./a.out < input.txt) expected.txt
```

`<(...)` runs the command and hands `diff` its output as if it were a file. Handy once the compile-test loop gets repetitive.

---

## A realistic test cycle

Putting it together, testing a counter program against a fixed input and a reference:

```sh
cc -Wall count.c -o count           # build with warnings on
printf 'a b  c\n\ttab line\n' > t.txt   # make a test file with known whitespace
od -c t.txt                         # confirm what's actually in it
./count < t.txt                     # run yours
wc t.txt                            # check against wc
```

---

*Once Shotts' book arrives, redirection, pipes, and permissions get the full treatment there — this is the subset that intersects directly with getting K&R programs to run and testing them.*
