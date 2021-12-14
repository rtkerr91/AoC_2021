
def parse_inputs(file: str):
    signal_list = []
    displays_list = []
    with open(file, 'r') as f:
        for line in f:
            signal_list.append(line.strip().split('|')[0].split())
            displays_list.append(line.strip().split('|')[1].split())

    return signal_list, displays_list


def solve_part_1(display_outputs: list):

    appearances = 0
    for display in display_outputs:
        for digit in display:
            n_segments = len(digit)

            if n_segments in (2, 3, 4, 7):
                appearances += 1

    return appearances


def _figure_out_translations(input_signal: list):
    length_5_signals = []
    length_6_signals = []
    solved_numbers = {'0': None, '1': None, '2': None, '3': None, '4': None,
                      '5': None, '6': None, '7': None, '8': None, '9': None}

    # Solve the easy signals for numbers 1, 4, 7, 8
    for signal in input_signal:
        if len(signal) == 2:
            solved_numbers['1'] = signal
        elif len(signal) == 3:
            solved_numbers['7'] = signal
        elif len(signal) == 4:
            solved_numbers['4'] = signal
        elif len(signal) == 7:
            solved_numbers['8'] = signal
        elif len(signal) == 5:
            length_5_signals.append(signal)
        else:
            length_6_signals.append(signal)

    # solve for segments bd which are used to solve for number 5
    segments_bd = []
    for segment in solved_numbers['4']:
        if segment not in solved_numbers['1']:
            segments_bd.append(segment)

    # Solve for segment a
    segment_a = []
    for segment in solved_numbers['7']:
        if segment not in solved_numbers['4']:
            segment_a.append(segment)

    # Solve for segment eg
    segments_eg = []
    for segment in solved_numbers['8']:
        if (segment not in solved_numbers['4']) and (segment not in segment_a):
            segments_eg.append(segment)

    # Solve the signals for numbers 2, 5, 3
    for signal in length_5_signals:

        # Solve for number 3
        bool_arr_3 = []
        for letter in solved_numbers['1']:
            if letter in signal:
                bool_arr_3.append(True)
            else:
                bool_arr_3.append(False)

        if all(bool_arr_3):
            solved_numbers['3'] = signal

        # Solve for number 5
        bool_arr_5 = []
        for segment in segments_bd:
            if segment in signal:
                bool_arr_5.append(True)
            else:
                bool_arr_5.append(False)

        if all(bool_arr_5):
            solved_numbers['5'] = signal

        if not all(bool_arr_3) and not all(bool_arr_5):
            solved_numbers['2'] = signal

    # Solve for segment d
    segment_d = []
    for segment in solved_numbers['3']:
        if (segment not in solved_numbers['1']) and (segment not in segment_a) and (segment not in segments_eg):
            segment_d.append(segment)

    # Solve the signals for numbers 9, 6, 0
    for signal in length_6_signals:

        # Solve for number 6
        bool_arr_6 = []
        for segment in solved_numbers['1']:
            if segment in signal:
                bool_arr_6.append(True)
            else:
                bool_arr_6.append(False)

        if not all(bool_arr_6):
            solved_numbers['6'] = signal

        else:
            if segment_d[0] in signal:
                solved_numbers['9'] = signal
            else:
                solved_numbers['0'] = signal

    sorted_solved_numbers = {}
    for number, segments in solved_numbers.items():
        temp = list(segments)
        temp.sort()
        sorted_solved_numbers[''.join(temp)] = number

    return sorted_solved_numbers


def _sort_display_segments(unsorted_displays: list):
    sorted_displays = []
    for display in unsorted_displays:
        temp = list(display)
        temp.sort()
        sorted_displays.append(''.join(temp))
    return sorted_displays


def solve_part_2(inputs_signals: list, output_displays: list):
    decoded_output = []

    for i, signal in enumerate(inputs_signals):
        segments_to_numbers = _figure_out_translations(signal)

        display = _sort_display_segments(output_displays[i])

        display_as_str = ''.join([segments_to_numbers[segments] for segments in display])
        decoded_output.append(display_as_str)

    return sum(map(int, decoded_output))


if __name__ == "__main__":
    input_file = r'inputs\inputs.txt'

    signals, displays = parse_inputs(input_file)

    part_1 = solve_part_1(displays)
    print(part_1)

    part_2 = solve_part_2(signals, displays)
    print(part_2)
