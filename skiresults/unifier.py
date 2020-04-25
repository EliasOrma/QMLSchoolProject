import io
import hashlib

'''
Used to reformat and check the original results to be similar all the way through
'''

def createID(result):
    for i in range(len(result)):
        result[i] = result[i].title()
    ingredients = "".join(result[6] + result[7] + result[9])
    ID = str(hashlib.md5(ingredients.encode('utf-8', errors='replace')).hexdigest())
    result = [ID] + result
    return result

def unifyTimes(result):
    ''' if len(result[2]) > 3:
        timeParts = result[2].split(':')
        timeParts.reverse()
        result.pop(2)
        for i in timeParts:
            result.insert(2,i)
    time = [result[2], result[3], result[4]] '''
    timeParts = result[2].split(':')
    if len(timeParts[0]) == 1:
        timeParts[0] = str(0)+timeParts[0]
    time = ":".join(timeParts)
    result[2] = time
    ''' result.pop(3)
    result.pop(3) '''
    
    return result

def main():
    Data = []
    with io.open('skiDatabyYearAndRoutes2.txt', 'r', encoding='utf8') as file:
        
        for line in file:
            
            if line[0] == '#' or line[0] == '~':
                Data.append(line)
                continue
            line.rstrip()
            
            line = line.split(';')
            if len(line) < 12:
                line.append(str(0))

            for i in range(len(line)):
                if line[i].encode('utf8') == b'\xc2\xa0':
                    line[i] = str(0)

            line = createID(line[1:])
            line = unifyTimes(line)

            stringForm = ";".join(line)
            Data.append(stringForm)

        
        file.close()
        
        
    with io.open('allRaceResultsByYear2.txt', 'w', encoding='utf8') as file:
        counter = 0
        for athelete in Data:
            counter += 1
            if counter % 1000 == 0:
                print(counter)
            
            file.write('{}'.format(athelete))

        #6 7 8 10 11
        '''
        def createID(result):
            ingredients = "".join(result[6] + result[7] + result[9])
            ID = str(hashlib.md5(ingredients.encode('utf-8', errors='replace')).hexdigest())
            result = [ID] + result
            return result
        laita .lower(), (TAI .TITLE() Kaikkialle.) sillä jos nimet on kirjoitettu eri kirjainkoolla, niin ID vaihtuu
        '''

        '''
            if line[0] == '~':
                curYear = line[1:]
                # print('Debug')
                continue
                
            if line[0] == '#':
                curRace = line[1:]
                # print('Debug')
                continue
        '''

main()