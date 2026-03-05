#!/bin/sh
# basic automated smoke tests for the minishell project
# run with: sh tests/minishell_tests.sh

MS=./minishell

echo "== compile check =="
make

echo "== simple builtins =="
echo "echo hello" | $MS

echo "== variable expansion =="
(echo "export TEST=qux"; echo "echo a\$TESTb"; echo exit) | $MS

echo "== quoting =="
( echo "export TEST=qux"; echo 'echo "a$TESTb"'; echo 'echo '\''a$TESTb'\'''; echo exit) | $MS

echo "== redirections & heredoc =="
( 
  echo "echo file1 > /tmp/mstest.txt";
  echo "echo file2 >> /tmp/mstest.txt";
  echo "cat /tmp/mstest.txt";
  echo "rm /tmp/mstest.txt";
  echo "cat <<EOF";
  echo "heredoc_line1";
  echo "heredoc_line2";
  echo "EOF";
  echo "ls /nonexistent";
  echo "echo $?";
  echo exit;
) | $MS

echo "== pipe and status =="
( echo "false | true"; echo "echo $?"; echo exit) | $MS

echo "== input redir =="
( echo "echo hi < /etc/hostname"; echo exit) | $MS

echo "== done =="
