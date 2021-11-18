# cloning repo
git clone url folderDestination

edit

# switch to branch
git checkout branchname

# git push flow
git status ; shows all modified files

git add file.txt / git add --all

git commit -m "commit name subject"
git commit

git push / git push origin

# checking and changing origin and upstream
git remote -v

git remote add origin url

git remote add upstream url

git fetch upstream

git merge upstream/main

# Remove the file from the repository
git rm --cached .idea/

# now update your gitignore file to ignore this folder
echo '.idea' >> .gitignore

# add the .gitignore file
git add .gitignore

git commit -m "Removed .idea files"
git push origin <branch>

# hub pull requests
hub --help pull-request  # do this first
                         # practice on a test repo
hub pull-request         # assumes origin on current_branch
git pull-request         # if you are using the git alias

# github CLI pull requests
gh pr create        # create pull request

#To assign a pull request to an individual, use the --assignee or -a flags. You can use @me to self-assign the pull request.
gh pr create --assignee "@octocat"

#To specify the branch into which you want the pull request merged, use the --base or -B flags. To specify the branch that contains commits for your pull request, use the --head or -H flags.
gh pr create --base my-base-branch --head my-changed-branch

#To include a title and body for the new pull request, use the --title and --body flags.
gh pr create --title "The bug is fixed" --body "Everything works again"

#To mark a pull request as a draft, use the --draft flag.
gh pr create --draft

#To add a labels or milestones to the new pull request, use the --label and --milestone flags.
gh pr create --label "bug,help wanted" --milestone octocat-milestone

#To add the new pull request to a specific project, use the --project flag.
gh pr create --project octocat-project

#To assign an individual or team as reviewers, use the --reviewer flag.
gh pr create --reviewer monalisa,hubot  --reviewer myorg/team-name

#To create the pull request in your default web browser, use the --web flag.
gh pr create --web
