INTRODUCTION
-----------
General Data Protection Regulation using One Trust.

This module intends to deal with the EU Directive on Data Protection Regulation
that comes into effect on 25th May 2018.
From that date, if you are not compliant or visibly not working towards
compliance, you run the risk of enforcement action, which can include a fine
for a serious breach.

The module displays a overlay at the top of website to make
users aware of the fact that cookies are being set. The user may then give
his/her consent or move to a page that provides more details. Consent is given
by user pressing the agree buttons or by continuing browsing the website.

The module provides a settings page to place the UUID which need to be procured
from OneTrust https://onetrust.com/.

DISCLAIMER
----------
This module comes without any warranty of any kind, including any
warranty (implied or otherwise) as to its fitness for a particular purpose.
In particular, whilst this module may help your website comply to privacy
legislation in various jurisdictions, you and you alone are responsible for
ensuring that your website complies with all necessary legislation.

REQUIREMENTS
------------
The module requires the website be scanned on OneTrust.
Categorize all cookies in OneTrust.
procure UUID for website.

INSTALLATION
------------

1. Unzip the files to the "sites/all/modules" directory and enable the module.

2. Give the administer or other roles permission to make changes on the
configuration page. You can do so on the admin/user/permissions page.


CONFIGURATION
-------------

1. Go to the admin/config/system/gdpr-onetrust page to place the UUID procured
from OneTrust.

Recommendation:
Assing the UUID in settings.php, change the variable based on language if applicable.
$conf['gdpr_onetrust_compliance_uuid'] = '<UUID value>';


2. You may want to create a cookie policy page that would explain how your site
uses cookies.

3. To display the cookie table on the cookie policy page place this div
<div id="optanon-cookie-policy"></div> in the desired location in cookie policy
page.

Or

Alternatively you can use the "One Trust Cookie table" block and place it
according to your site build.

4. To place the cookie settings button on the website you can place the
menu item "Cookie Settings" from admin/structure/menu/manage/user-menu to
footer menu of the website.

or

place the link <a class="optanon-show-settings">Cookie Settings</a> in desired
location on the website.

or

Alternatively you can use the "One Trust cookie settings" block and place it
according to your site build.

NOTICE: The module does not audit your cookies nor does it prevent cookies
from being set.