import os
import itertools

servs = ["nginx-thrift","media-service","compose-post-service","user-service","unique-id-service","text-service","user-mention-service",
         "user-timeline-service","post-storage-service","url-shorten-service","write-home-timeline-service","social-graph-service"]
hostnames=["clemth.irisa.fr", "clempc"]
outDir="out/"
templateFile="docker-compose_template.yml"

def already_in(pos, posList):
    for pp in posList:
        already = True
        for p in pos:
            if not p in pp:
                already = False
        if(already):
            return True
    return False

def write_awk_for_config(config, hosts, fname="tmp.awk"):
    # add a gsub for each service so that we can get from the template to an operational docker-compose.yml
    with open(fname, 'w') as file:
        file.write("NR >= 1 {\n")
        for i in range(len(hosts)):
            for j in config[i]:
                file.write("gsub(/%%%s%%/,\"%s\");\n"%(j, hosts[i]))
        file.write("print;\n}")

def write_csv_for_sg(config, hosts, fname="configsg.csv", default="default"):
    with open(fname, 'w') as file:
        for i in range(len(hosts)):
            for j in config[i]:
                file.write("%s %s\n"%(j, hosts[i]))
        file.write("default %s"%(default))
# almost copy pasted from https://stackoverflow.com/questions/38217594/no-of-ways-of-placing-k-distinguishable-items-into-n-distinguishable-boxes
def make_sets(items, num_of_boxes=3):
    allpossible = []

    for tup in itertools.product(range(num_of_boxes), repeat=len(items)):
        boxes = [list() for _ in range(num_of_boxes)]
        for item, box in zip(items, tup):
            boxes[box].append(item)
        if(not already_in(boxes, allpossible)):
            allpossible.append(boxes)

    return allpossible

class Drawing:
    forms = ""
    def __init__(self, width=500, height=250):
        self.forms = ""
        self.width = width
        self.height = height

    def writeToFile(self, name):
        f = open(name, "w")

        f.write('''<?xml version="1.0" encoding="utf-8"?>\n''')
        f.write('''<svg xmlns="http://www.w3.org/2000/svg" version="1.1" width="'''+str(self.width)+'''" height="'''+str(self.height)+'''">\n''')
        f.write("<title>"+name+"</title>\n")
        f.write(self.forms)
        f.write("</svg>")
        f.close()

    def draw_rect(self, width, height, x, y, col="orange"):
        self.forms += "<rect width=\""+str(width)+"\" height=\""+str(height)+"\" x=\""+str(x)+"\" y=\""+str(y)+"\" fill=\""+col+"\" stroke=\"#000\" stroke-width=\"3\" "+"/>"

    def draw_line(self, x1,x2,y1,y2,col="black"):
        self.forms += "<line x1=\""+str(x1)+"\" y1=\""+str(y1)+"\" x2=\""+str(x2)+"\" y2=\""+str(y2)+"\" stroke=\""+col+"\"/>\n"

    def draw_text(self, text, x, y, weight="normal"):
        self.forms += "<text x=\"%d\" y=\"%d\" font-weight=\"%s\">%s</text>"%(x, y,weight,text)

def createPic(positions, fname):
    h = 500
    graph = Drawing(len(hostnames)*(250+40),h+10)
    posTxt=[3]*len(positions)

    for i in range(len(hostnames)):
        graph.draw_rect(250,h,5+i*(250+35),5, col="rgb(174, 213, 129)")
        graph.draw_rect(220,35,10+i*(250+35),1, col="rgb(255, 245, 157)")
        graph.draw_text("HOST: "+hostnames[i], 13+i*(250+35),28, weight="bold")
        for j in p[i]:
            print("serv %s on node %s"%(j,hostnames[i]))
            graph.draw_text(j, 10+i*(250+35),5+posTxt[i]*25)
            posTxt[i]+=1

    graph.writeToFile(fname)




positions = make_sets(servs, num_of_boxes=len(hostnames))

#for p in positions:
#    for box in p:
#        print (str(box).ljust(50),end="")
#    print()


for pi in range(len(positions)):
    print("------------------------\nNew configuration")
    p = positions[pi]
    awkPath=outDir+"/%d_awkfile.awk"%(pi)
    sgPath=outDir+"/%d_sg.csv"%(pi)
    write_awk_for_config(p, hostnames, fname=awkPath)
    write_csv_for_sg(p,hostnames, fname=sgPath)
    os.system("awk -f %s %s  > %s/%d_docker_compose.yml"%(awkPath,templateFile,outDir,pi))
    createPic(p, outDir+"/%d_deployment.svg"%(pi))
    for i in range(len(hostnames)):
        for j in p[i]:
            print("serv %s on node %s"%(j,hostnames[i]))

