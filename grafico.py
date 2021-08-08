import pandas as pd
import matplotlib.pyplot as plt

fortranDataFrame = pd.read_csv('temposFortran.csv')
CDataFrame = pd.read_csv('temposC.csv')

figura, eixos = plt.subplots(1,2,figsize=(10,5), sharey=False)

fortranDataFrame.plot.line(x = 'n', y = 'TempoIJ', ax = eixos[1], ylabel='Tempo em segundos')
fortranDataFrame.plot.line(x = 'n', y = 'TempoJI', ax = eixos[1])
eixos[1].set_title('Fortran',fontsize=12)

CDataFrame.plot.line(x = 'n', y = 'TempoIJ', ax = eixos[0], ylabel='Tempo em segundos')
CDataFrame.plot.line(x = 'n', y = 'TempoJI', ax = eixos[0])
eixos[0].set_title('C',fontsize=12)


figura.savefig('grafico.jpeg')
