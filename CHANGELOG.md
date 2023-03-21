# IPK project 1 2022/2023 - Changelog

## Supported functionality
Program is capable of establishing TCP or UDP connection, sending user input to server and handling of Ctrl + C user interrupt signal.

Program arguments can be passed in any order.

## Known limitations
- UDP communication does not have implemented timeout for case when some message is lost
- UDP communication can be terminated only by Ctrl + C