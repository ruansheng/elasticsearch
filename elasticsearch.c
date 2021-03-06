/*
  +----------------------------------------------------------------------+
  | PHP Version 7                                                        |
  +----------------------------------------------------------------------+
  | Copyright (c) 1997-2017 The PHP Group                                |
  +----------------------------------------------------------------------+
  | This source file is subject to version 3.01 of the PHP license,      |
  | that is bundled with this package in the file LICENSE, and is        |
  | available through the world-wide-web at the following url:           |
  | http://www.php.net/license/3_01.txt                                  |
  | If you did not receive a copy of the PHP license and are unable to   |
  | obtain it through the world-wide-web, please send a note to          |
  | license@php.net so we can mail you a copy immediately.               |
  +----------------------------------------------------------------------+
  | Author:                                                              |
  +----------------------------------------------------------------------+
*/

/* $Id$ */

#ifdef HAVE_CONFIG_H
#include "config.h"
#endif

#include "php.h"
#include "php_ini.h"
#include "ext/standard/info.h"
#include "php_elasticsearch.h"

#include "elasticsearch_client.h"

/* If you declare any globals in php_elasticsearch.h uncomment this:
ZEND_DECLARE_MODULE_GLOBALS(elasticsearch)
*/

/* True global resources - no need for thread safety here */
static int le_elasticsearch;

/* {{{ PHP_INI
 */
/* Remove comments and fill if you need to have entries in php.ini
PHP_INI_BEGIN()
    STD_PHP_INI_ENTRY("elasticsearch.global_value",      "42", PHP_INI_ALL, OnUpdateLong, global_value, zend_elasticsearch_globals, elasticsearch_globals)
    STD_PHP_INI_ENTRY("elasticsearch.global_string", "foobar", PHP_INI_ALL, OnUpdateString, global_string, zend_elasticsearch_globals, elasticsearch_globals)
PHP_INI_END()
*/
/* }}} */

/* Remove the following function when you have successfully modified config.m4
   so that your module can be compiled into PHP, it exists only for testing
   purposes. */

/* {{{ proto string printElasticSearchDocument()
   Return a string to confirm that the module is compiled in */
PHP_FUNCTION(printElasticSearchDocument)
{
	php_printf("--- ElasticSearch PHP7 Ext Document ---\n");
	php_printf("     function printElasticSearchDocument();\n");
	php_printf("     class ElasticSearchClient\n");
	php_printf("         public static $connect_timeout = 1000;  // unit:ms  default:1000ms\n");
	php_printf("         public static $request_timeout = 2000;  // unit:ms  default:2000ms\n");
	php_printf("         private $host = \"\";\n");
	php_printf("         private $port = \"\";\n");
	php_printf("         private $message = \"\";\n");
	php_printf("         public function __construct(string $host, int $port)\n");
	php_printf("         public function add($params) : mixed\n");
	php_printf("         public function remove($params) : mixed\n");
	php_printf("         public function update($params) : mixed\n");
	php_printf("         public function get($params) : mixed\n");
	php_printf("         public function search($params) : mixed\n");
	php_printf("         public function getMessage() : string\n");
	php_printf("         public static function setConnectTimeout($millisecond) : bool\n");
	php_printf("         public static function setRequestTimeout($millisecond) : bool\n");
}
/* }}} */
/* The previous line is meant for vim and emacs, so it can correctly fold and
   unfold functions in source code. See the corresponding marks just before
   function definition, where the functions purpose is also documented. Please
   follow this convention for the convenience of others editing your code.
*/


/* {{{ php_elasticsearch_init_globals
 */
/* Uncomment this function if you have INI entries
static void php_elasticsearch_init_globals(zend_elasticsearch_globals *elasticsearch_globals)
{
	elasticsearch_globals->global_value = 0;
	elasticsearch_globals->global_string = NULL;
}
*/
/* }}} */

/* {{{ PHP_MINIT_FUNCTION
 */
PHP_MINIT_FUNCTION(elasticsearch)
{
	/* If you have INI entries, uncomment these lines
	REGISTER_INI_ENTRIES();
	*/

	ELASTICSEARCH_STARTUP(client);

	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MSHUTDOWN_FUNCTION
 */
PHP_MSHUTDOWN_FUNCTION(elasticsearch)
{
	/* uncomment this line if you have INI entries
	UNREGISTER_INI_ENTRIES();
	*/
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request start */
/* {{{ PHP_RINIT_FUNCTION
 */
PHP_RINIT_FUNCTION(elasticsearch)
{
#if defined(COMPILE_DL_ELASTICSEARCH) && defined(ZTS)
	ZEND_TSRMLS_CACHE_UPDATE();
#endif
	return SUCCESS;
}
/* }}} */

/* Remove if there's nothing to do at request end */
/* {{{ PHP_RSHUTDOWN_FUNCTION
 */
PHP_RSHUTDOWN_FUNCTION(elasticsearch)
{
	return SUCCESS;
}
/* }}} */

/* {{{ PHP_MINFO_FUNCTION
 */
PHP_MINFO_FUNCTION(elasticsearch)
{
	php_info_print_table_start();
	php_info_print_table_header(2, "elasticsearch support", "enabled");
	php_info_print_table_end();

	/* Remove comments if you have entries in php.ini
	DISPLAY_INI_ENTRIES();
	*/
}
/* }}} */

/* {{{ elasticsearch_functions[]
 *
 * Every user visible function must have an entry in elasticsearch_functions[].
 */
const zend_function_entry elasticsearch_functions[] = {
	PHP_FE(printElasticSearchDocument,	NULL)		/* For testing, remove later. */
	PHP_FE_END	/* Must be the last line in elasticsearch_functions[] */
};
/* }}} */

/* {{{ elasticsearch_module_entry
 */
zend_module_entry elasticsearch_module_entry = {
	STANDARD_MODULE_HEADER,
	"elasticsearch",
	elasticsearch_functions,
	PHP_MINIT(elasticsearch),
	PHP_MSHUTDOWN(elasticsearch),
	PHP_RINIT(elasticsearch),		/* Replace with NULL if there's nothing to do at request start */
	PHP_RSHUTDOWN(elasticsearch),	/* Replace with NULL if there's nothing to do at request end */
	PHP_MINFO(elasticsearch),
	PHP_ELASTICSEARCH_VERSION,
	STANDARD_MODULE_PROPERTIES
};
/* }}} */

#ifdef COMPILE_DL_ELASTICSEARCH
#ifdef ZTS
ZEND_TSRMLS_CACHE_DEFINE()
#endif
ZEND_GET_MODULE(elasticsearch)
#endif

/*
 * Local variables:
 * tab-width: 4
 * c-basic-offset: 4
 * End:
 * vim600: noet sw=4 ts=4 fdm=marker
 * vim<600: noet sw=4 ts=4
 */
