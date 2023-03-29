#! /usr/bin/env python3
# Solution: https://stackoverflow.com/questions/19425857/env-python-r-no-such-file-or-directory
import unittest

import json
import ujson
import cjson

class TestStringMethods(unittest.TestCase):
    def test_load(self):
        json_str = '{"hello": 10, "world": "value"}'

        json_doc = json.loads(json_str)
        ujson_doc = ujson.loads(json_str)

        cjson_doc = cjson.loads(json_str)

        self.assertEqual(json_doc, cjson_doc)
        self.assertEqual(ujson_doc, cjson_doc)

    def test_dump(self):
        json_str = '{"hello": 10, "world": "value"}'
    
        self.assertEqual(json_str, cjson.dumps(cjson.loads(json_str)))

if __name__ == '__main__':
    unittest.main()
