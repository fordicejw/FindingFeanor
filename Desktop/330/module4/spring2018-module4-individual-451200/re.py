import re

def reg_test(reg_test, string):
    match = reg_test.match(string)
    if match is not None:
        return match.group(1)
    else:
        return False

hi = 'This is a string to test the occurrence of hello world vs helloworld vs \
      hi world vs hello'
hi_regex = re.compile(r"[\bhello\sworld\b/i]")

reg_test(hi_regex, hi)

print ('\n\n')

# --

vowels = 'This is a string to test occurence of words w/ three consecutive \
          vowels like beauty, tableau, and Maui.'
vowels_regex = re.compile(r"[\b\w*[aeiou]{3}\w*\b]")

reg_test(vowels_regex, vowels)

print ('\n\n')

# --

flight = 'A2345 \
          AA234 \
          AA2345 \
          BZ3 \
          Cow \
          FO0845'

flight_regex = re.compile(r"[\b[A-Z]{2}\d{3,4}]")

reg_test(flight_regex, flight)
