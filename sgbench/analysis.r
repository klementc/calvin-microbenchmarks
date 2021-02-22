library(ggplot2)
library(dplyr)
library(tidyr)
library(tikzDevice)
library(gridExtra)
library(zoo)

getwd()
setwd("/home/clem/Code/github.com/klementc/calvin-microbenchmarks/sgbench/res/")
data <- read.csv("results.csv")

#gh <- ggplot(data2, aes(x=timestamps))+geom_histogram(binwidth=1)
# "plot(gh)


gi <- ggplot(data, aes(x=flops, y=endEx-qArr))+
  geom_point(size=3)+
  ylim(0, 4)+ stat_summary(fun=mean, geom="line", colour="green", size =3)
#  expand_limits(y = 0)
plot(gi)
ggsave("plot_dur.png")

gj <- ggplot(data, aes(x=ts, y=endEx-qArr))+
  geom_point(size=1)+
  facet_wrap("flops", scales="free")+
  geom_line(aes(y=rollmean(endEx-qArr, 50, na.pad=TRUE)), color="green")+
  geom_line(aes(y=rollmedian(endEx-qArr, 30, na.pad=TRUE)), color="yellow")
plot(gj)
ggsave("plot_instcnt.png")

data2 <- read.csv("../default5TimeStamps.csv")

gh <- ggplot(data2, aes(x=data2[,1]))+geom_histogram(binwidth=1)
plot(gh)
