import pyuaf


def test(args):
    
    print("util.localizedtext")
    
    print(" - testing pyuaf.util.LocalizedText()")
    
    l0  = pyuaf.util.LocalizedText("en", "Some Text")
    l0_ = pyuaf.util.LocalizedText("en", "Some Text")
    l1  = pyuaf.util.LocalizedText("en", "Some Other Text")
    
    print(" - testing pyuaf.util.LocalizedText().locale()")
    assert l0.locale() == "en"
    
    print(" - testing pyuaf.util.LocalizedText().text()")
    assert l0.text() == "Some Text"
    
    print(" - testing pyuaf.util.LocalizedText().__eq__()")
    assert l0 == l0_
    assert not (l0 == l1)
    
    print(" - testing pyuaf.util.LocalizedText().__ne__()")
    assert l0 != l1
    assert not (l0 != l0_)
    
    print(" - testing pyuaf.util.LocalizedText().__lt__()")
    assert l1 < l0
    
    print(" - testing pyuaf.util.LocalizedText().__gt__()")
    assert l0 > l1
