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


# if ! repo_is_clean ; then
#     echo "git repo has uncommited changes pending"
#     exit 1
# fi

./buildabot.sh
if [ ! $? ]; then
    echo "build error"
    exit 2
fi

GIT_COMMIT=`git rev-parse HEAD`
NEEDS_TAG=`git describe --contains ${GIT_COMMIT} 2>/dev/null`

#only tag if no tag already (would be better if the git describe command above could have a silent option)
if [ -z "${NEEDS_TAG}" ]; then
    #get highest tag number
    VERSION=`git describe --abbrev=0 --tags 2>/dev/null`

    #replace . with space so can split into an array
    VERSION_BITS=(${VERSION//./ })

    #get number parts and increase last one by 1
    VNUM1=${VERSION_BITS[0]}
    VNUM2=${VERSION_BITS[1]}
    VNUM3=${VERSION_BITS[2]}
    VNUM3=$((VNUM3+1))

    #create new tag
    NEW_TAG="$VNUM1.$VNUM2.$VNUM3"

    echo "Updating ${VERSION} to ${NEW_TAG}"

    echo "Tagged with ${NEW_TAG}"
    git tag ${NEW_TAG}
    #git push --tags

    BOT_NAME="MyBot_${NEW_TAG}"    
    mv MyBot "${BOT_NAME}"
else
    echo "Already a tag on this commit"
fi

echo "finished"

