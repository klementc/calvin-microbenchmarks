NR >= 1 {
gsub(/%nginx-thrift%/,"clemth.irisa.fr");
gsub(/%media-service%/,"clemth.irisa.fr");
gsub(/%user-service%/,"clemth.irisa.fr");
gsub(/%text-service%/,"clemth.irisa.fr");
gsub(/%user-timeline-service%/,"clemth.irisa.fr");
gsub(/%url-shorten-service%/,"clemth.irisa.fr");
gsub(/%compose-post-service%/,"clempc");
gsub(/%unique-id-service%/,"clempc");
gsub(/%user-mention-service%/,"clempc");
gsub(/%post-storage-service%/,"clempc");
print;
}