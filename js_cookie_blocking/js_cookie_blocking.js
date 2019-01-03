/**
 * @file
 * The OneTrust API data and categories filter, and cookie deletion.
 */
var gdprDelete = function () {

  /**
   * Get the list of disabled category ids
   *  @param {array} activegroups The activegroup array from OneTrust.
   *  @param {array} cookie_category The cookie category Ids from website..
   *  @returns {array} The disabled category ids.
   */
  var getDisabledCategory = function (activegroups, cookie_category) {

    var res = activegroups.split(',');
    var disabled = [];
    cookie_category.forEach(function (c_category) {
      if (Array.isArray(res) === true) {
        if (jQuery.inArray(String(c_category), res) == -1) {
          disabled.push(c_category);
        }
      }
    });
    return disabled;
  };

  /**
   * Generate a list of cookies to delete
   * @param {array} cookie_list The full list of cookies.
   * @param {array} cookie_category_id The disabled category.
   * @param {array} cookies_to_block The cookies to block.
   */
  var getDisabledCookies = function (cookie_list, cookie_category_id, cookies_to_block) {
    if (cookie_list.length > 0) {
      if (cookie_category_id === 2) {
        cookies_to_block.performance_cookie.push(cookie_list);
      }
      else if (cookie_category_id === 3) {
        cookies_to_block.functional_cookie.push(cookie_list);
      }
      else if (cookie_category_id === 4) {
        cookies_to_block.targeting_cookie.push(cookie_list);
      }
      else if (cookie_category_id === 8) {
        cookies_to_block.media_cookie.push(cookie_list);
      }
      prepareDeleteCookie(cookie_list);
    }
  };

  /**
   * Delete the cookie from the site domain.
   * @param {array} c_list The list of cookies.
   */
  var prepareDeleteCookie = function (c_list) {
    c_list.forEach(function (c_names) {
      deleteCookie(c_names.Name);
      if(jQuery.cookie(c_names.Name) !== null) {
        deleteCookie(c_names.Name, 'partdomain');
      }
    });
  };

  /**
   * Delete the cookies.
   * @param {array} c_name The cookie name.
   * @param {array} c_host The cookie host.
   */
  var deleteCookie = function (c_name, c_host) {
    var params = {};
    params['expires'] = 'Thu, 01-Jan-70 00:00:01 GMT';
    if (c_host === 'partdomain') {
      //Will apply only when the dev/stage domains are set in cookie.
      var part_domains = Drupal.settings.js_cookie_blocking.base_domain.split(".");
      var last = part_domains.pop();
      var second_last = part_domains.pop();
      part_domains.push(second_last+"."+last);
      part_domains.push("."+second_last+"."+last);
      part_domains.push(Drupal.settings.js_cookie_blocking.base_domain);
      part_domains.push("."+Drupal.settings.js_cookie_blocking.base_domain);
      part_domains.reverse();
      part_domains.forEach(function (part_domain) {
        var path = "/";
        document.cookie = c_name + '=' +
          ((path) ? '; path=' + path : '') +
          ((part_domain) ? '; domain=' + part_domain : '') +
          '; expires='+params.expires;
        if(jQuery.cookie(c_name) === null) {
          return true;
        }
      });
    }
    else {
      jQuery.cookie(c_name, null);
    }
  };

  return {
    assignCookie : function () {
      var cookies_to_block = {performance_cookie: [], functional_cookie: [], targeting_cookie: [], media_cookie: []};
      var cookie_category = [2, 3, 4, 8];

      var disabled_cookie_category = getDisabledCategory(OptanonActiveGroups, cookie_category);

      if (typeof disabled_cookie_category !== 'undefined' && disabled_cookie_category.length > 0) {
        var domaindata = Optanon.GetDomainData();
        var domaindata_length = domaindata.Groups.length;
        var parrent_groupid = [];
        var i, j;

        //Fetch the parent category ID and cookies
        for (i = 1; i < domaindata_length; i++) {
          if (jQuery.inArray(domaindata.Groups[i].OptanonGroupId, disabled_cookie_category) !== -1) {
            getDisabledCookies(domaindata.Groups[i].Cookies, domaindata.Groups[i].OptanonGroupId, cookies_to_block);
            parrent_groupid.push([domaindata.Groups[i].OptanonGroupId, domaindata.Groups[i].GroupId]);
          }
        }
        //Fetch the sub category cookies belonging to parent categories.
        for (j = 1; j < domaindata_length; j++) {
          if (domaindata.Groups[j].Parent !== null && domaindata.Groups[j].Parent) {
            parrent_groupid.forEach(function (p_group) {
              if (p_group[1] == domaindata.Groups[j].Parent.GroupId) {
                getDisabledCookies(domaindata.Groups[j].Cookies, p_group[0], cookies_to_block);
              }
            });
          }
        }
      }

      jQuery.post("/gdpr/cookie_blocking", {
        "gdpr_c": OptanonActiveGroups,
        "cookie_toblock": JSON.stringify(cookies_to_block)
      });
    }
  };
};