import io
import hashlib

'''
With this we can log all the different atheletes who have attended the race
'''

def createID(result):
    for i in range(len(result)):
        result[i] = result[i].title()
    ingredients = "".join(result[6] + result[7] + result[9])
    ID = str(hashlib.md5(ingredients.encode('utf-8', errors='replace')).hexdigest())
    result = [ID] + result
    return result


def main():
    allAtheletes = {}
    curYear = 0
    curRace = ''
    with io.open('skiDataByYearAndRoutes.txt', 'r', encoding='utf8') as file:
        for line in file:
            if line[0] == '~':
                curYear = line[1:]
                # print('Debug')
                continue
                
            if line[0] == '#':
                curRace = line[1:]
                # print('Debug')
                continue

            else:
                line = line.split(';')
                line = createID(line[1:])

                if line[0] not in allAtheletes:
                    allAtheletes[line[0]] = line[6:]
                    # print('Debug2')


        file.close()
        with io.open('athleteData.txt', 'w', encoding='utf8') as file:
            for athelete in allAtheletes:
                stringForm = ";".join([athelete] + allAtheletes[athelete])
                #print(stringForm)
                file.write(stringForm)

        #6 7 8 10 11
        '''
        def createID(result):
            ingredients = "".join(result[6] + result[7] + result[9])
            ID = str(hashlib.md5(ingredients.encode('utf-8', errors='replace')).hexdigest())
            result = [ID] + result
            return result
        laita .lower(), (TAI .TITLE() Kaikkialle.) sillä jos nimet on kirjoitettu eri kirjainkoolla, niin ID vaihtuu
        '''

main()