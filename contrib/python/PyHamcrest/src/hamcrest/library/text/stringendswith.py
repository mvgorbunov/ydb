from hamcrest.library.text.substringmatcher import SubstringMatcher 
from hamcrest.core.helpers.hasmethod import hasmethod 
 
__author__ = "Jon Reid" 
__copyright__ = "Copyright 2011 hamcrest.org" 
__license__ = "BSD, see License.txt" 
 
 
class StringEndsWith(SubstringMatcher): 
 
    def __init__(self, substring): 
        super(StringEndsWith, self).__init__(substring) 
 
    def _matches(self, item): 
        if not hasmethod(item, 'endswith'): 
            return False 
        return item.endswith(self.substring) 
 
    def relationship(self): 
        return 'ending with' 
 
 
def ends_with(string): 
    """Matches if object is a string ending with a given string. 
 
    :param string: The string to search for. 
 
    This matcher first checks whether the evaluated object is a string. If so, 
    it checks if ``string`` matches the ending characters of the evaluated 
    object. 
 
    Example:: 
 
        ends_with("bar") 
 
    will match "foobar". 
 
    """ 
    return StringEndsWith(string) 
