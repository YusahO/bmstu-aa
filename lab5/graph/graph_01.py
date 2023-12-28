#!./graph/venv/bin/python
# import matplotlib.pyplot as plt
# import numpy as np
#
"""
512 19 10
513 17 11

1024 21 11
1025 19 12

2048 23 12
2049 21 13

4096 25 13
4097 23 14

8192 27 14
8193 25 15
"""

"""
512 17 10
513 1 10

1024 19 11
1025 1 11

2048 21 12
2049 1 12

4096 23 13
4097 1 13

8192 25 14
8193 1 14
"""

"""
512 20 9
513 20 10

1024 22 10
1025 22 11

2048 24 11
2049 24 12

4096 26 12
4097 26 13

8192 28 13
8193 28 14
"""

import matplotlib.pyplot as plt
import numpy as np

# species = ('512', '513', '1024', '1025', '2048', '2049', '4096', '4097', '8192', '8193')
# penguin_means = {
#     'С 1 сравнением':(17, 1, 19, 1, 21, 1, 23, 1, 25, 1),
#     'С 2 сравнениями':(10, 10, 11, 11, 12, 12, 13, 13, 14, 14),
# }

species = ('512', '513', '1024', '1025', '2048', '2049', '4096', '4097', '8192', '8193')
penguin_means = {
    'С 1 сравнением':(20, 20, 22, 22, 24, 24, 26, 26, 28, 28),
    'С 2 сравнениями':(9, 10, 10, 11, 11, 12, 12, 13, 13, 14),
}

# species = ('512', '513', '1024', '1025', '2048', '2049', '4096', '4097', '8192', '8193')
# penguin_means = {
#     'С 1 сравнением':(19, 17, 21, 19, 23, 21, 25, 23, 27, 25),
#     'С 2 сравнениями':(10, 11, 11, 12, 12, 13, 13, 14, 14, 15),
# }

x = np.arange(len(species))  # the label locations
width = 0.25  # the width of the bars
multiplier = 0

fig, ax = plt.subplots(layout='constrained')

for attribute, measurement in penguin_means.items():
    offset = width * multiplier
    rects = ax.bar(x + offset, measurement, width, label=attribute)
    ax.bar_label(rects, padding=3)
    multiplier += 1

# Add some text for labels, title and custom x-axis tick labels, etc.
ax.set_ylabel('Length (mm)')
ax.set_title('Поиск элемента (худший случай: элемента нет)')
ax.set_xticks(x + width, species)
ax.legend(loc='upper left', ncols=3)
# ax.set_ylim(0, 250)

plt.show()
