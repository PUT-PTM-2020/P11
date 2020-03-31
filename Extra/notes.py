import numpy as np
import pandas as pd

CLOCK_MCU = 84000000
TOLERANCE = 0.01

notes = [
    ("pp ", 1),
    ("C2 ", 6500),
    ("CS2", 6900),
    ("D2 ", 7300),
    ("DS2", 7800),
    ("E2 ", 8200),
    ("F2 ", 8700),
    ("FS2", 9200),
    ("G2 ", 9800),
    ("GS2", 10400),
    ("A2 ", 11000),
    ("AS2", 11700),
    ("B2 ", 12300),
    ("C3 ", 13100),
    ("CS3", 13900),
    ("D3 ", 14700),
    ("DS3", 15600),
    ("E3 ", 16500),
    ("F3 ", 17500),
    ("FS3", 18500),
    ("G3 ", 19600),
    ("GS3", 20800),
    ("A3 ", 22000),
    ("AS3", 23300),
    ("B3 ", 24700),
    ("C4 ", 26200),
    ("CS4", 27700),
    ("D4 ", 29400),
    ("DS4", 31100),
    ("E4 ", 33000),
    ("F4 ", 34900),
    ("FS4", 37000),
    ("G4 ", 39200),
    ("GS4", 41500),
    ("A4 ", 44000),
    ("AS4", 46600),
    ("B4 ", 49400),
    ("C5 ", 52300),
    ("CS5", 55400),
    ("D5 ", 58700),
    ("DS5", 62200),
    ("E5 ", 65900),
    ("F5 ", 69800),
    ("FS5", 74000),
    ("G5 ", 78400),
    ("GS5", 83100),
    ("A5 ", 88000),
    ("AS5", 93200),
    ("B5 ", 98800),
    ("C6 ", 104700),
    ("CS6", 110900),
    ("D6 ", 117500),
    ("DS6", 124500),
    ("E6 ", 131800),
    ("F6 ", 139700),
    ("FS6", 148000),
    ("G6 ", 156800),
    ("GS6", 166100),
    ("A6 ", 176000),
    ("AS6", 186500),
    ("B6 ", 197600),
    ("C7 ", 209300)
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
            if arr <= 65536:
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
    if error < tolerance and arr < 65536.0:
        h = hertz(CLOCK_MCU, psc, int(arr))
        return psc, int(arr), h, error
    else:
        return None


#  ------------------------------------------------------------------------

f = open("notes.c", "w")
f.write("void setNote(char* note, TIM_HandleTypeDef* htim){\n")
for note, freq in notes:
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
    f.write("   if(note == \""+note+"\"){\n")
    f.write("       htim->Instance->PSC = "+psc+";\n")
    f.write("       htim->Instance->ARR = "+str(arr if int(arr) > 0 else 1)+";\n")
    f.write("   }\n")
    print(note + " generated.")
f.write("}")
exit(0)
