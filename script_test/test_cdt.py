import pytest
import unittest
import os

class test_cdt(unittest.TestCase):

	def test_1_compression_create_file(self):
		os.system('cd ../src && ./cdt -c -m testcompression.cpp -f ../file_test/alla.txt')
		test=os.path.exists("../file_test/alla.txt.cdt")
		self.assertTrue(test)

	def test_2_decompression_create_file(self):
		os.system('rm ../file_test/alla.txt')
		os.system('cd ../src && ./cdt -d -m testcompression -f ../file_test/alla.txt.cdt')
		test=os.path.exists("../file_test/alla.txt")
		self.assertTrue(test)

	def test_3_compression_create_file_multiple(self):
		os.system('cd ../src && ./cdt -c -m testcompression -f "../file_test/allb.txt ../file_test/allc.txt"')
		test1=os.path.exists("../file_test/allb.txt.cdt")
		test2=os.path.exists("../file_test/allc.txt.cdt")
		self.assertTrue(test1)
		self.assertTrue(test2)

	def test_4_decompression_create_file_multiple(self):
		os.system('rm ../file_test/allb.txt')
		os.system('rm ../file_test/allc.txt')
		os.system('cd ../src && ./cdt -d -m testcompression -f "../file_test/allb.txt.cdt ../file_test/allc.txt.cdt"')
		test1=os.path.exists("../file_test/allb.txt")
		test2=os.path.exists("../file_test/allc.txt")
		self.assertTrue(test1)
		self.assertTrue(test2)

	def test_5_rebuilt_file_content(self):
		os.system('echo "aaaaaaaaaa" >> ../file_test/alla.txt')
		f1=open('../file_test/alla.txt','r')
		f1c=f1.read()
		f1.close()
		os.system('rm ../file_test/alla.txt.cdt')
		os.system('cd ../src && ./cdt -c -m testcompression -f ../file_test/alla.txt')
		os.system('rm ../file_test/alla.txt')
		os.system('cd ../src && ./cdt -d -m testcompression -f ../file_test/alla.txt.cdt')
		f2=open('../file_test/alla.txt','r')
		f2c=f2.read()
		f2.close()
		self.assertEqual(f1c,f2c)

	def test_6_rebuilt_file_content_bigger_file(self):
		os.system('cat ../file_test/random.txt >> ../file_test/alld.txt')
		f1=open('../file_test/alld.txt','r')
		f1c=f1.read()
		f1.close()
		os.system('rm ../file_test/alld.txt.cdt')
		os.system('cd ../src && ./cdt -c -m testcompression -f ../file_test/alld.txt')
		os.system('rm ../file_test/alld.txt')
		os.system('cd ../src && ./cdt -d -m testcompression -f ../file_test/alld.txt.cdt')
		f2=open('../file_test/alld.txt','r')
		f2c=f2.read()
		f2.close()
		self.assertEqual(f1c,f2c)
		

	def test_7_make_clean(self):
		#not a test, just reset testing environment
		os.system('cd ../src && make clean')
		test1=os.path.exists("../file_test/alla.txt")
		test2=os.path.exists("../file_test/allb.txt")
		test3=os.path.exists("../file_test/allc.txt")
		test4=os.path.exists("../file_test/alld.txt")
		test11=os.path.exists("../file_test/alla.txt.cdt")
		test22=os.path.exists("../file_test/allb.txt.cdt")
		test33=os.path.exists("../file_test/allc.txt.cdt")
		test44=os.path.exists("../file_test/alld.txt.cdt")
		self.assertTrue(test1 and test2 and test3 and not test4 and not test11 and not test22 and not test33 and not test44)
