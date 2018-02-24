import sys, os, re

if len(sys.argv) < 2:
	sys.exit("Usage: %s filename insert filename" % sys.argv[0])

filename = sys.argv[1]

if not os.path.exists(filename):
	sys.exit("Error: File '%s' not found" % sys.argv[1])

# Create empty list to be populated with player names

names = []

# Create dictionaries to be populated with player data

bat_dict = {} # {name:num_at_bat}
hit_dict = {} # {name:num_hits}
avg_dict = {} # {name:bat_avg}


# Create regex expressions

name_re = re.compile(r"\b[A-Z][a-z]+\s[A-Z][a-z]+\b")

bat_re = re.compile(r"\b(?<=batted\s)\d\b")

num_hits_re = re.compile(r"\b(?<=times with\s)\d\b")

f = open(filename, 'r')
lines = f.readlines()[4:]
for line in lines:
    if name_re.match(line) is not None:
            name = name_re.match(line).group()
            bat_match = bat_re.search(line).group()
            hit_match = num_hits_re.search(line).group()
            names.append(name)
            if name not in bat_dict:
                bat_dict[name] = int(bat_match)
            else:
                bat_dict[name] += int(bat_match)
            if name not in hit_dict:
                hit_dict[name] = int(hit_match)
            else:
                hit_dict[name] += int(hit_match)
f.close()

# Compute averages now that dictionaries are populated

for name in names:
    avg_dict[name] = float(hit_dict[name]) / float(bat_dict[name])

# Sort players by batting average and print output
# Source: https://stackoverflow.com/questions/20944483/python-3-sort-a-dict-by-its-values

s = [(k, avg_dict[k]) for k in sorted(avg_dict, key=avg_dict.get, reverse=True)]
for k, v in s:
	 print('%s: %s' % (k, "{:.3f}".format(v)))
