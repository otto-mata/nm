FROM fedora:latest

RUN dnf update -y && dnf install -y \
	gcc.x86_64 \
	glibc-devel.i686 \
	glibc-devel.x86_64 \
	libatomic.x86_64 \
	libatomic.i686

ENTRYPOINT ["make"]
