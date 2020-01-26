from tkinter import *
from tkinter.filedialog import askopenfilename
from PIL import Image
from PIL import ImageTk
from PIL import ImageGrab
from ctypes import windll #Makes app DPI Aware
user32 = windll.user32
user32.SetProcessDPIAware()
#import Image, ImageTk
count=1
XCoordinates = []
YCoordinates = []
XYCoordinates = []
text_ids = []
costs = {}


if __name__ == "__main__":
    root = Tk()

    # open image and set width and height
    File = askopenfilename(parent=root, initialdir="C:/",title='Choose an image.')
    im = Image.open(File)
    widths, heights = im.size
    img = ImageTk.PhotoImage(im)
    
    #setting up a tkinter canvas with scrollbars
    frame = Frame(root, bd=2, relief=SUNKEN,height=heights,width=widths)
    frame.grid_rowconfigure(0, weight=1)
    frame.grid_columnconfigure(0, weight=1)
    #xscroll = Scrollbar(frame, orient=HORIZONTAL)
    #xscroll.grid(row=1, column=0, sticky=E+W)
    #yscroll = Scrollbar(frame)
    #yscroll.grid(row=0, column=1, sticky=N+S)
    canvas = Canvas(frame, bd=0)#, xscrollcommand=xscroll.set, yscrollcommand=yscroll.set)
    canvas.grid(row=0, column=0, sticky=N+S+E+W)
    #xscroll.config(command=canvas.xview)
    #yscroll.config(command=canvas.yview)
    frame.pack(fill=BOTH,expand=1)

    #adding the image
    canvas.create_image(0,0,image=img,anchor="nw")
    # canvas.config(scrollregion=canvas.bbox(ALL))

    #Bubble Sort
    def inRange(a,b):
        return a-40<=b<=a+40
    def bSort(lst):
        isSorted=0
        while not isSorted:
            isSorted=1
            for i in range(len(lst)-1):
                if not inRange(lst[i][1],lst[i+1][1]) and lst[i][1]>lst[i+1][1]:
                    lst[i],lst[i+1]=lst[i+1],lst[i]
                    isSorted=0
                elif inRange(lst[i][1],lst[i+1][1]) and lst[i][0]>lst[i+1][0]:
                    lst[i],lst[i+1]=lst[i+1],lst[i]
                    isSorted=0
        return lst



    #function to be called when mouse is clicked
    def printcoords(event):
        #outputting x and y coords to console
        global text_ids
        global count
        global XCoordinates 
        global YCoordinates 
        global XYCoordinates
        print(round(event.x/(widths/360)),round((heights-event.y)/(heights/270)))   	
        #print(event.x,(event.y) )
        #XCoordinates.append(event.x//3)
        #YCoordinates.append((heights-event.y)//3)
        oval_id = canvas.create_oval(event.x-20,event.y-20,event.x+20,event.y+20,outline = 'red',width = 5)
        text_id = canvas.create_text(event.x,event.y,text=str(count),font = "Times 20 italic bold")
        XYCoordinates.append((event.x,event.y,oval_id,text_id)) 

        #Sort Nodes according to Y then X
        
        text_ids.append(text_id)

        XYCoordinates = bSort(XYCoordinates)
        #Delete all nodes and redraw them according to sorting results
        for i in text_ids:
            canvas.delete(i)

        text_ids = []
        for i in range(1,len(XYCoordinates)+1):
            text_id = canvas.create_text(XYCoordinates[i-1][0],XYCoordinates[i-1][1],text=str(i),font = "Times 20 italic bold")
            text_ids.append(text_id)
            
        count+=1



    #mouseclick event
    canvas.bind("<Button 1>",printcoords)

    #Quit when done
    def Exit(*args):

        with open('NodeResults.txt','w') as f:
            Xresult = '0,'
            Yresult = '0,'
            for i in XYCoordinates:
                temp1,temp2 = i[0],i[1]
                temp1 = str(round(temp1/(widths/360)))                  
                temp2 = str(round((heights-temp2)/(heights/270)))
                Xresult+=temp1+(3-len(temp1))*' '+','
                Yresult+=temp2+(3-len(temp2))*' '+','
            Xresult = Xresult[:-1]
            Yresult = Yresult[:-1]
            f.write(Xresult+'\n'+Yresult+'\n\n\n')
            for key in costs:
                #key = [(X,Y,ID,ID)][(X,Y,ID,ID)]
                node1_id,node2_id = key.split('][')
                node1_id,node2_id = tuple(map(int,(node1_id[2:-1]).split(','))),tuple(map(int,(node2_id[1:-2]).split(',')))
                node1_id = XYCoordinates.index(node1_id)+1
                node2_id = XYCoordinates.index(node2_id)+1
                
                f.write('cost['+str(node1_id)+']['+str(node2_id)+'] = '+str(costs[key][0])+';\n')




                #f.write('('+str(XYCoordinates[i][0]//3)+','+str((heights-XYCoordinates[i][1])//3)+')\n')

        x=canvas.winfo_rootx()+canvas.winfo_x()
        y=canvas.winfo_rooty()+canvas.winfo_y()
        x1=x+canvas.winfo_width()
        y1=y+canvas.winfo_height()
        new_canvas = (x,y,x1,y1)
        new_canvas = ImageGrab.grab(bbox=new_canvas).save("out_snapsave.jpg")
        root.destroy()
	
    canvas.bind("<Button 2>",Exit)
	

    #Delete nodes and redraw them
    def deleteNode(event):
        global count
        global text_ids
        global XYCoordinates
        tempx = event.x
        tempy = event.y
        temp_id = None
        for i in XYCoordinates:
            if tempx<(i[0]+6) and tempx>(i[0]-6) and tempy<(i[1]+6) and tempy>(i[1]-6):
                canvas.delete(i[2])
                canvas.delete(i[3])
                temp_id = XYCoordinates.index(i)
                break

        if temp_id!=None:
            #Delete all cost paths connected to node
            cost_deleter = XYCoordinates[temp_id]
            for nodes in costs.copy():
                if str(cost_deleter) in nodes:
                    print(str(nodes) + ' has been deleted!')
                    canvas.delete(costs[nodes][2])
                    canvas.delete(costs[nodes][1])
                    del costs[nodes]

            del XYCoordinates[temp_id]
            canvas.delete(text_ids[temp_id])
            del text_ids[temp_id]

            for i in text_ids:
                canvas.delete(i)
            text_ids = []
            if XYCoordinates!=[]:
                XYCoordinates = bSort(XYCoordinates)
            for i in range(1,len(XYCoordinates)+1):
                text_id = canvas.create_text(XYCoordinates[i-1][0],XYCoordinates[i-1][1],text=str(i),font = "Times 20 italic bold")
                text_ids.append(text_id)
            count-=1
            print('Node has been deleted!')

    canvas.bind('<Button 3>',deleteNode)

    #Create Cost in Dictionary
    #[node1][node2] = (cost,line_id,cost_id)
    #def create_cost(node1,node2,cost,costs)
    def create_cost():
        global costs
        global query
        string = query.get()
        query.delete(0,END)
        node1,node2,cost = map(int,string.split())
        node1,node2 = min(node1,node2),max(node1,node2)
        
        if node1>len(XYCoordinates) or node2>len(XYCoordinates):
            print('Node is out of range!')

        else:
            node1XY = XYCoordinates[node1-1]
            node2XY = XYCoordinates[node2-1]

            if '[{}][{}]'.format(node1XY,node2XY) in costs.keys(): #Replace cost
                canvas.delete(costs['[{}][{}]'.format(node1XY,node2XY)][2])
                temp_id = costs['[{}][{}]'.format(node1XY,node2XY)][1]
                temp_textID = canvas.create_text((XYCoordinates[node1-1][0]+XYCoordinates[node2-1][0])/2,(XYCoordinates[node1-1][1]+XYCoordinates[node2-1][1])/2,text=str(cost),font = "Times 20 italic bold")
                costs['[{}][{}]'.format(node1XY,node2XY)] = (cost,temp_id,temp_textID)
                print('Cost path replaced!')
            else: #Create new cost
                temp_id = canvas.create_line(XYCoordinates[node1-1][0],XYCoordinates[node1-1][1],XYCoordinates[node2-1][0],XYCoordinates[node2-1][1],width=5,fill = 'red')
                temp_textID = canvas.create_text((XYCoordinates[node1-1][0]+XYCoordinates[node2-1][0])/2,(XYCoordinates[node1-1][1]+XYCoordinates[node2-1][1])/2,text=str(cost),font = "Times 20 italic bold")
                costs['[{}][{}]'.format(node1XY,node2XY)] = (cost,temp_id,temp_textID)
                print('Cost path created!')

    def delete_cost():
        global costs
        global query
        string = query.get()
        query.delete(0,END)
        useless = list(map(int,string.split())) 
        node1,node2 = min(useless[0],useless[1]),max(useless[0],useless[1])
        node1XY = XYCoordinates[node1-1]
        node2XY = XYCoordinates[node2-1]
        if '[{}][{}]'.format(node1XY,node2XY) not in costs.keys():
            print('Cost path does not exist!')
        else:
            canvas.delete(costs['[{}][{}]'.format(node1XY,node2XY)][2])
            canvas.delete(costs['[{}][{}]'.format(node1XY,node2XY)][1])
            del costs['[{}][{}]'.format(node1XY,node2XY)]
            print('Cost path removed!')


    def load_file():
        global XYCoordinates
        global costs
        costs = {}
        XYCoordinates = []
        XCoordinates = []
        YCoordinates = []
        text_file = askopenfilename( initialdir="C:/", title="select file", filetypes=(("text files", "*.txt"), ("all files", "*.*")))
        print(text_file)
        with open(text_file,'r') as reader:
            for i,line in enumerate(reader):
                if i==0:
                    XCoordinates = line.rstrip('\n').split(',')[1:]
                elif i==1:
                    YCoordinates = line.rstrip('\n').split(',')[1:]
                    break
            XCoordinates=list(map(lambda x: round(int(x)*(widths/360)),XCoordinates))
            YCoordinates=list(map(lambda x: round((270*heights-int(x)*heights)/270),YCoordinates)) #print(round(event.x/(widths/360)),round((heights-event.y)/(heights/270))) 
            #Create nodes
            for i in range(len(XCoordinates)):
                oval_id = canvas.create_oval(XCoordinates[i]-20,YCoordinates[i]-20,XCoordinates[i]+20,YCoordinates[i]+20,outline = 'red',width = 5)
                text_id = canvas.create_text(XCoordinates[i],YCoordinates[i],text=str(i+1),font = "Times 20 italic bold")
                XYCoordinates.append((XCoordinates[i],YCoordinates[i],oval_id,text_id)) 
            #Create cost paths
            for i,line in enumerate(reader):
                if i>1 and line.rstrip('\n')!='':
                    temp_line = line.rstrip('\n')
                    temp_line = temp_line.split('=')
                    temp_node1,temp_node2 = ''.join(temp_line[0]).split('][')
                    temp_cost = temp_line[1]
                    temp_node1=temp_node1[5:]
                    temp_node2=temp_node2[:-2]
                    temp_cost=temp_cost[1:-1]
                    temp_node1,temp_node2,temp_cost=int(temp_node1),int(temp_node2),int(temp_cost)
                    node1XY = XYCoordinates[temp_node1-1]
                    node2XY = XYCoordinates[temp_node2-1]
                    temp_id = canvas.create_line(XYCoordinates[temp_node1-1][0],XYCoordinates[temp_node1-1][1],XYCoordinates[temp_node2-1][0],XYCoordinates[temp_node2-1][1],width=5,fill = 'red')
                    temp_textID = canvas.create_text((XYCoordinates[temp_node1-1][0]+XYCoordinates[temp_node2-1][0])/2,(XYCoordinates[temp_node1-1][1]+XYCoordinates[temp_node2-1][1])/2,text=str(temp_cost),font = "Times 20 italic bold")
                    costs['[{}][{}]'.format(node1XY,node2XY)] = (temp_cost,temp_id,temp_textID)
        print('File has been loaded!')



    #Create Entry Widget
    query = Entry(root)
    query.pack()
    #Focus the Entry Widget
    query.focus_set()
    query.focus_force()
    #Create buttons
    remove_button = Button(root,text='Delete Cost Path',command=delete_cost)
    remove_button.pack(side='bottom')
    create_button = Button(root,text='Create Cost Path',command=create_cost)
    create_button.pack(side='bottom')
    exit_button = Button(root,text='Exit',command=Exit)
    exit_button.pack(side='right')
    load_button = Button(root,text='Load File',command=load_file)
    load_button.pack(side='right')


    root.mainloop()
	
	
	
	
	
	
	