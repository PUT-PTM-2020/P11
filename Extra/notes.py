import numpy as np
import pandas as pd

CLOCK_MCU = 84000000
TOLERANCE = 0.01
SAMPLING_RATE = 50

notes = [
    ("pp ", 1),
    ("C2 ", 65),
    ("CS2", 69),
    ("D2 ", 73),
    ("DS2", 78),
    ("E2 ", 82),
    ("F2 ", 87),
    ("FS2", 92),
    ("G2 ", 98),
    ("GS2", 104),
    ("A2 ", 110),
    ("AS2", 117),
    ("B2 ", 123),
    ("C3 ", 131),
    ("CS3", 139),
    ("D3 ", 147),
    ("DS3", 156),
    ("E3 ", 165),
    ("F3 ", 175),
    ("FS3", 185),
    ("G3 ", 196),
    ("GS3", 208),
    ("A3 ", 220),
    ("AS3", 233),
    ("B3 ", 247),
    ("C4 ", 262),
    ("CS4", 277),
    ("D4 ", 294),
    ("DS4", 311),
    ("E4 ", 330),
    ("F4 ", 349),
    ("FS4", 370),
    ("G4 ", 392),
    ("GS4", 415),
    ("A4 ", 440),
    ("AS4", 466),
    ("B4 ", 494),
    ("C5 ", 523),
    ("CS5", 554),
    ("D5 ", 587),
    ("DS5", 622),
    ("E5 ", 659),
    ("F5 ", 698),
    ("FS5", 740),
    ("G5 ", 784),
    ("GS5", 831),
    ("A5 ", 880),
    ("AS5", 932),
    ("B5 ", 988),
    ("C6 ", 1047),
    ("CS6", 1109),
    ("D6 ", 1175),
    ("DS6", 1245),
    ("E6 ", 1318),
    ("F6 ", 1397),
    ("FS6", 1480),
    ("G6 ", 1568),
    ("GS6", 1661),
    ("A6 ", 1760),
    ("AS6", 1865),
    ("B6 ", 1976),
    ("C7 ", 2093)
]

# -----------------------------------------------------


def abs_error(num1, num2):
    return abs((num1 - num2) / num1)


def hertz(clock, prescaler, period):
    f = clock / (prescaler * period)
    return f


def perfect_divisors(trg_f):
    exacts = []
    for psc in range(1, 65536):
        arr = CLOCK_MCU / (trg_f * psc)
        if CLOCK_MCU % psc == 0:
            if arr <= 65536 and arr >= 2:
                exacts.append(psc)
    return exacts


def add_exact_period(prescaler, trg_f):
    entries = []
    arr = CLOCK_MCU / (trg_f * prescaler)
    if arr == int(arr):
        entry = [prescaler, arr, trg_f, 0.0]
        entries.append(entry)
    return entries


def possible_prescaler_value(trg_f):
    possibles = []
    for psc in range(1, 65536):
        if psc in exact_prescalers:
            continue
        h1 = hertz(CLOCK_MCU, psc, 1)
        h2 = hertz(CLOCK_MCU, psc, 65536)
        if h1 >= trg_f >= h2:
            possibles.append(psc)
    return possibles


def close_divisor(psc, tolerance, trg_f):
    arr = CLOCK_MCU / (trg_f * psc)
    error = abs_error(int(arr), arr)
    if error < tolerance and arr < 65536.0 and arr >= 2:
        h = hertz(CLOCK_MCU, psc, int(arr))
        return psc, int(arr), h, error
    else:
        return None


#  ------------------------------------------------------------------------

f = open("notes.c", "w")
f.write("void setNote(char* note, TIM_HandleTypeDef* htim){\n")
notes_sampled = [(x[0], x[1] * 100) for x in notes]
for note, freq in notes_sampled:
    df = pd.DataFrame(columns=['PSC', 'ARR', 'F', 'ERROR'], dtype=np.double)
    exact_prescalers = perfect_divisors(freq)
    exact_values = []
    for index in range(len(exact_prescalers)):
        rows = add_exact_period(exact_prescalers[index], freq)
        for rowindex in range(len(rows)):
            df = df.append(pd.DataFrame(
                np.array(rows[rowindex]).reshape(1, 4), columns=df.columns))

    poss_prescalers = possible_prescaler_value(freq)
    close_prescalers = []
    for index in range(len(poss_prescalers)):
        value = close_divisor(poss_prescalers[index], TOLERANCE, freq)
        if value is not None:
            close_prescalers.append((value[0], value[1], value[2], value[3]))
    df = df.append(pd.DataFrame(np.array(close_prescalers).reshape(
        len(close_prescalers), 4), columns=df.columns))

    df['PSC'] = df['PSC'] - 1
    df['ARR'] = df['ARR'] - 1

    df = df.sort_values(['ERROR', 'PSC'])

    df['EXACT'] = pd.Series("?", index=df.index)
    df['EXACT'] = np.where(df['ERROR'] == 0.0, "YES", "NO")

    df['PSC'] = df['PSC'].map('{:.0f}'.format)
    df['ARR'] = df['ARR'].map('{:.0f}'.format)
    df['F'] = df['F'].map('{:.6f}'.format)
    df['ERROR'] = df['ERROR'].map('{:.10f}'.format)

    psc = df.iloc[0].loc["PSC"]
    arr = df.iloc[0].loc["ARR"]
    f.write("   if(strcmp(note, \""+note+"\") == 0){\n")
    f.write("       htim->Instance->PSC = "+psc+";\n")
    f.write("       htim->Instance->ARR = "+arr+";\n")
    f.write("   }\n")
    print(note + " generated.")
f.write("}")
exit(0)
