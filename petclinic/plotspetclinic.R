library(ggplot2)
library(dplyr)
library(tidyr)
library(tikzDevice)
library(gridExtra)
library(ggpubr)

setwd("/home/clem/Code/github.com/klementc/calvin-microbenchmarks/petclinic/")

datarw <- as_tibble(read.csv("./summaryPetClinic.csv"))

gc <- ggplot() +
  geom_point(data = datarw, aes(x=load, y=throughput, group=sample, colour=factor(sample)),alpha=.8)+
  geom_line(data = datarw, aes(x=load, y=throughput, group=sample, colour=factor(sample)),alpha=.8)
plot(gc)


gc <- ggplot() +
  geom_point(data = datarw, aes(x=load, y=meanLatency, group=sample, colour=factor(sample)),alpha=.8)+
  geom_line(data = datarw, aes(x=load, y=meanLatency, group=sample, colour=factor(sample)),alpha=.8)
plot(gc)

gc <- ggplot() +
  geom_point(data = datarw, aes(x=load, y=medianLatency, group=sample, colour=factor(sample)),alpha=.8)+
  geom_line(data = datarw, aes(x=load, y=medianLatency, group=sample, colour=factor(sample)),alpha=.8)
plot(gc)