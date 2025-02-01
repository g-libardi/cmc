import csv

with open('lex_table.csv', 'r', newline='') as f:
    reader = csv.reader(f)
    table = list(reader)

char_classes = table[0][1:]
states = [r[0] for r in table[1:]]

print('char_classes =', char_classes)
print('states =', states)

code = f'''
    typedef enum {{
        {',\n'.join(states)}
        OK,
        ERROR
    }} State;

    typedef enum {{
        {',\n    '.join(char_classes)}
    }} CharClass;

    State transition_table[{len(states)}][{len(char_classes)}] = {{
        {',\n'.join([f'{{{", ".join(r[1:])}}}' for r in table[1:]])}
}};
'''

with open('out.c', 'w') as f:
    f.write(code)
