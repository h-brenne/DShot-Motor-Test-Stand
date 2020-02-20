
import numpy as np
import matplotlib.pyplot as plt
import sys
import func

Motor="iFlight XING 4214"#Enter motor name
Propeller="T-Motor CF 18x6.1"#Enter motor name
kV="400"#Enter motor kV
testName="FullTest"
thrustFile = "fulltest.csv"
pngimg="4214.png"


data = np.genfromtxt(thrustFile, delimiter=',', skip_header=1,
                     names=['Time_ms', 'dshot', 'Voltage_V', 'Current_A', 'RPM', 'Thrust_g', 'Torque_Nm', 'Ambient_temp_C', 'Motor_temp_C', 'ESC_temp_C'])

#Get index of the different tests
index30=func.timestampData(15000,data['Time_ms'])
index30end=func.timestampData(17000,data['Time_ms'])

index40=func.timestampData(17000,data['Time_ms'])
index40end=func.timestampData(19000,data['Time_ms'])

index50=func.timestampData(19000,data['Time_ms'])
index50end=func.timestampData(21000,data['Time_ms'])

index75=func.timestampData(21000,data['Time_ms'])
index75end=func.timestampData(23000,data['Time_ms'])

index100=func.timestampData(23000,data['Time_ms'])
index100end=func.timestampData(25000,data['Time_ms'])

indexGrad=func.timestampData(27000,data['Time_ms'])
indexGradEnd=func.timestampData(33000,data['Time_ms'])

# Remove bad values
motTemp = []
for el in data['Motor_temp_C']:
    if el<180:
        motTemp.append(el)
    else:
        motTemp.append(25)
ambTemp= []
for el in data['Ambient_temp_C']:
    if el<180:
        ambTemp.append(el)
    else:
        ambTemp.append(25)

# Only plotting gPerW at reasonable throttle levels
gPerW = []
for i in range(len(data['Time_ms'])):
    if ((i-100 > index30 and i < index30end) or (i-100 > index40 and i < index40end) or
            (i-100 > index50 and i < index50end) or (i-100 > index75 and i < index75end)
    or (i-100>index100 and i < index100end) or (i-40>indexGrad and i < indexGradEnd)):
        gPerW.append(abs(data['Thrust_g'][i])/((data['Voltage_V'][i]+0.0001)*(data['Current_A'][i]+0.001)))
    else:
        gPerW.append(0)

# Setup total figure
fig = plt.figure(figsize=(15,20))

# First table with general information
tab1 = fig.add_subplot(6,2,1)
tab1Data = [[Motor],[Propeller],[kV],[testName]]
columns = ("1")
rows = ["Motor","Propeller","kV", "Test"]
row_Colors = []
for i in range (len(rows)):
    if i%2 ==0:
        row_Colors.append("#F2F2F2")
    else:
        row_Colors.append("w")
cell_Colors = []
for i in range (len(tab1Data)):
    if i%2 ==0:
        cell_Colors.append(["#F2F2F2"])
    else:
        cell_Colors.append(["w"])
table1 = plt.table(cellText=tab1Data, cellColours=cell_Colors, rowLabels=rows,rowColours=row_Colors, bbox=(0.4,0,0.7,1))
table1.auto_set_font_size(False)
table1.set_fontsize(14)
tab1.axis('off')


imgmot = fig.add_subplot(622)
arr = plt.imread(pngimg)
img = imgmot.imshow(arr)
imgmot.axis('off')
fig.subplots_adjust(top=0.95)

thrust30=int(round(func.meanInterval(abs(data['Thrust_g']),index30+100,index30end)))
voltage30=round(func.meanInterval(abs(data['Voltage_V']),index30+100,index30end),2)
current30=round(func.meanInterval(abs(data['Current_A']),index30+100,index30end),2)
rpm30=int(round(func.meanInterval(abs(data['RPM']),index30+100,index30end)))
power30=int(round(voltage30*current30))
gW30 = round(func.meanInterval(gPerW ,index30+100,index30end),2)
torque30=int(round(func.meanInterval(abs(data['Torque_Nm']*0.06),index30+100,index30end)))
motTemp30=int(round(func.meanInterval(motTemp,index30+100,index30end)))

thrust40=int(round(func.meanInterval(abs(data['Thrust_g']),index40+100,index40end)))
voltage40=round(func.meanInterval(abs(data['Voltage_V']),index40+100,index40end),2)
current40=round(func.meanInterval(abs(data['Current_A']),index40+100,index40end),2)
rpm40=int(round(func.meanInterval(abs(data['RPM']),index40+100,index40end)))
power40=int(round(voltage40*current40))
gW40 = round(func.meanInterval(gPerW ,index40+100,index40end),2)
torque40=int(round(func.meanInterval(abs(data['Torque_Nm']*0.06),index40+100,index40end)))
motTemp40=int(round(func.meanInterval(motTemp,index40+100,index40end)))

thrust50=int(round(func.meanInterval(abs(data['Thrust_g']),index50+100,index50end)))
voltage50=round(func.meanInterval(abs(data['Voltage_V']),index50+100,index50end),2)
current50=round(func.meanInterval(abs(data['Current_A']),index50+100,index50end),2)
rpm50=int(round(func.meanInterval(abs(data['RPM']),index50+100,index50end)))
power50=int(round(voltage50*current50))
gW50 = round(func.meanInterval(gPerW ,index50+100,index50end),2)
torque50=int(round(func.meanInterval(abs(data['Torque_Nm']*0.06),index50+100,index50end)))
motTemp50=int(round(func.meanInterval(motTemp,index50+100,index50end)))

thrust75=int(round(func.meanInterval(abs(data['Thrust_g']),index75+100,index75end)))
voltage75=round(func.meanInterval(abs(data['Voltage_V']),index75+100,index75end),2)
current75=round(func.meanInterval(abs(data['Current_A']),index75+100,index75end),2)
rpm75=int(round(func.meanInterval(abs(data['RPM']),index75+100,index75end)))
power75=int(round(voltage75*current75))
gW75 = round(func.meanInterval(gPerW ,index75+100,index75end),2)
torque75=int(round(func.meanInterval(abs(data['Torque_Nm']*0.06),index75+100,index75end)))
motTemp75=int(round(func.meanInterval(motTemp,index75+100,index75end)))

thrust100=int(round(func.meanInterval(abs(data['Thrust_g']),index100+100,index100end)))
voltage100=round(func.meanInterval(abs(data['Voltage_V']),index100+100,index100end),2)
current100=round(func.meanInterval(abs(data['Current_A']),index100+100,index100end),2)
rpm100=int(round(func.meanInterval(abs(data['RPM']),index100+100,index100end)))
power100=int(round(voltage100*current100))
gW100 = round(func.meanInterval(gPerW ,index100+100,index100end),2)
torque100=int(round(func.meanInterval(abs(data['Torque_Nm']*0.06),index100+100,index100end)))
motTemp100=int(round(func.meanInterval(motTemp,index100+100,index100end)))

tab3 = fig.add_subplot(6,1,2)
tab3Data = [["30",thrust30,voltage30,current30,rpm30,power30,gW30, torque30, motTemp30],
            ["40",thrust40,voltage40,current40,rpm40,power40,gW40, torque40, motTemp40],
            ["50",thrust50,voltage50,current50,rpm50,power50,gW50, torque50, motTemp50],
            ["75",thrust75,voltage75,current75,rpm75,power75, gW75, torque75, motTemp75],
            ["100",thrust100,voltage100,current100,rpm100,power100, gW100, torque100, motTemp100]]


columns = ["Throttle[%]", "Thrust[g]","Voltage[V]","Current[A]","RPM","Power[W]","Efficiency[g/W]","Torque[Nm]","Motor Temp[C]"]
cell_Colors = []
for i in range (len(tab3Data)):
    if i%2 ==0:
        cell_Colors.append(["#F2F2F2"]*len(tab3Data[0]))
    else:
        cell_Colors.append(["w"]*len(tab3Data[0]))
table2 = plt.table(cellText=tab3Data, cellColours=cell_Colors, colLabels=columns, bbox=(-0.1,-0.6,1.4,1.7))
tab3.axis('off')

table2.auto_set_font_size(False)
table2.set_fontsize(12)

ax1 = fig.add_subplot(513)
fig.subplots_adjust(right=0.75)
ax2 = ax1.twinx()
ax3 = ax1.twinx()
ax3.spines["right"].set_position(("axes", 1.2))

ax3.plot(data['Time_ms'], data['dshot']/10.48, color='y', label='dshot')
ax3.set_xlabel('Time_ms')
ax3.set_ylabel('dshot')
ax3.set_ylim([0, 109])
ax3.set_xlim([13000, 35000])
ax3.spines["right"].set_bounds(0, 100)



ax2.plot(data['Time_ms'], gPerW, color='r', label='g/W')
ax2.set_ylabel('g/W')
ax2.set_ylim([0, 18])
ax2.legend()

ax1.plot(data['Time_ms'], abs(data['Thrust_g']), color='b', label='Thrust (g)')
ax1.set_ylabel('Thrust (g)')
ax1.set_ylim([0, 8000])
ax1.legend(loc="upper left")


ax1 = fig.add_subplot(514)
fig.subplots_adjust(right=0.75)
ax2 = ax1.twinx()
ax3 = ax1.twinx()
ax3.spines["right"].set_position(("axes", 1.2))

ax3.plot(data['Time_ms'], data['dshot']/10.48, color='y', label='dshot')
ax3.set_xlabel('Time_ms')
ax3.set_ylabel('dshot')
ax3.set_ylim([0, 109])
ax3.set_xlim([13000, 35000])
ax3.spines["right"].set_bounds(0, 100)

ax2.plot(data['Time_ms'], data['Voltage_V'], color='r', label='Voltage (V)')
ax2.set_ylabel('Voltage (V)')
ax2.set_ylim([25, 35])
ax2.legend()

ax1.plot(data['Time_ms'], data['Current_A'], color='b', label='Current (A)')
ax1.set_ylabel('Current (A)')
ax1.set_ylim([0, 80])
ax1.legend(loc="upper left")


ax1 = fig.add_subplot(515)
fig.subplots_adjust(right=0.75)
ax2 = ax1.twinx()
ax3 = ax1.twinx()
ax3.spines["right"].set_position(("axes", 1.2))


ax3.plot(data['Time_ms'], data['dshot']/10.48, color='y', label='dshot')
ax3.set_xlabel('Time_ms')
ax3.set_ylabel('dshot')
ax3.set_ylim([0, 109])
ax3.set_xlim([13000, 35000])
ax3.spines["right"].set_bounds(0, 100)

ax1.plot(data['Time_ms'], data['RPM'], color='r', label='RPM')
ax1.set_ylabel('RPM')
ax1.set_ylim([0, 12000])
ax1.legend(loc="upper left")
ax2.plot(data['Time_ms'], motTemp, color='b', label='Motor Temp')
ax2.set_ylabel('C')
ax2.set_ylim([15, 40])
ax2.legend()

fig.savefig(thrustFile+'.plot.png', dpi=200)
fig.savefig(thrustFile+'plot.pdf', dpi=200)