import os
import itertools

servs = ["nginx-thrift","media-service","compose-post-service","user-service","unique-id-service","text-service","user-mention-service","user-timeline-service","post-storage-service","url-shorten-service"]
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


positions = make_sets(servs, num_of_boxes=2)

#for p in positions:
#    for box in p:
#        print (str(box).ljust(50),end="")
#    print()


for pi in range(len(positions)):
    print("------------------------\nNew configuration")
    p = positions[pi]
    awkPath=outDir+"/%d_awkfile.awk"%(pi)
    write_awk_for_config(p, hostnames, fname=awkPath)
    os.system("awk -f %s %s  > %s/docker_compose_%d.yml"%(awkPath,templateFile,outDir,pi))

    for i in range(len(hostnames)):
        for j in p[i]:
            print("serv %s on node %s"%(j,hostnames[i]))
            
