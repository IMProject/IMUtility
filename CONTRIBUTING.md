We are happy to see contributions. You can add utility code that you see is missing, improve existing one, or open issue tickets. 
Before you open PR:
- write unit tests for your code
- run `make gcovr-report`, open `gcovr-report/coverage.html`, and make sure you made 100% code coverage for changes
- run `make format`
- run `make cppcheck`
- run `make misra`

After PR is opened, ECLAIR will check your code and Bot will report if any MISRA violation exists in the code. 
After all violations are fixed, we will review your code, and after that code can be merged into the main branch.
