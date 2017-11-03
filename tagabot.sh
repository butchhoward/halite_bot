#!/usr/bin/env bash

function repo_is_clean() 
{
    git update-index -q --ignore-submodules --refresh

    # unstaged changes in the working tree
    if ! git diff-files --quiet --ignore-submodules --
    then
        return 1
    fi

    # uncommitted changes in the index
    if ! git diff-index --cached --quiet HEAD --ignore-submodules --
    then
        return 2
    fi

    return 0
}

if ! repo_is_clean ; then
    echo "git repo has uncommited changes pending"
    exit 1
fi

HASH=$(git rev-parse --short HEAD)
BOT_NAME="MyBot_${HASH}"

./buildabot.sh
if [ ! $? ]; then
    echo "build error"
    exit 2
fi

mv MyBot "${BOT_NAME}"
echo "finished"

