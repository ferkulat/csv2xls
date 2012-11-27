#ACLOCAL_AMFLAGS = -I m4

if COND_TESTS
       MAYBE_TESTS = testing
endif
SUBDIRS = src  doc $(MAYBE_TESTS)

EXTRA_DIST = README.TXT LICENSE.TXT mingwbuild.sh Changelog.txt \
	     bootstrap.sh INSTALL.TXT ToDo.TXT

clean-local:
	rm -rf doc/html doc/latex
