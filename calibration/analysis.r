library(ggplot2)
library(dplyr)
library(tidyr)
library(tikzDevice)
library(gridExtra)

getwd()
setwd("/home/clem/Code/github.com/klementc/calvin-microbenchmarks/calibration/")
data <- read.csv("results.csv")

#gh <- ggplot(data2, aes(x=timestamps))+geom_histogram(binwidth=1)
# "plot(gh)


gi <- ggplot(data, aes(x=iter, y=dur))+
  geom_point(size=3)+
  geom_line(color="blue")+
  expand_limits(y = 0)
plot(gi)
ggsave("plot_dur.png")

gj <- ggplot(data, aes(x=iter, y=instcnt))+
  geom_point(size=1)+
  geom_line(color="blue")+
  expand_limits(y = 0)
plot(gj)
ggsave("plot_instcnt.png")
