<?php

class jsonHandler
{

    private static $messages = array(
        JSON_ERROR_DEPTH => 'The maximum stack depth has been exceeded',
        JSON_ERROR_STATE_MISMATCH => 'Syntax error, malformed JSON',
        JSON_ERROR_CTRL_CHAR => 'Unexpected control character found',
        JSON_ERROR_SYNTAX => 'Syntax error, malformed JSON',
        5 /*JSON_ERROR_UTF8*/ => 'Invalid UTF-8 sequence',
        6 /*JSON_ERROR_RECURSION*/ => 'Recursion detected',
        7 /*JSON_ERROR_INF_OR_NAN*/ => 'Inf and NaN cannot be JSON encoded',
        8 /*JSON_ERROR_UNSUPPORTED_TYPE*/ => 'Type is not supported',
    );


    public static function Encode($obj)
    {
        return json_encode($obj);
    }
   
   // public static function Decode($json, $toAssoc = false)
    //{
       // $result = json_decode($json, $toAssoc);
        //switch(json_last_error())
       // {
          //  case JSON_ERROR_DEPTH:
               // $error =  ' - Maximum stack depth exceeded';
                //break;
           // case JSON_ERROR_CTRL_CHAR:
                //$error = ' - Unexpected control character found';
                //break;
           // case JSON_ERROR_SYNTAX:
               // $error = ' - Syntax error, malformed JSON';
                //break;
           // case JSON_ERROR_NONE:
            //default:
               // $error = '';                   
        //}
        //if (!empty($error))
            //throw new Exception('JSON Error: '.$error);       
       
        //return $result;
    //}
    
    
    public static function decode($json)
    {
        if (!preg_match('##u', $json)) { // workaround for PHP < 5.3.3 & PECL JSON-C
            throw new JsonException('Invalid UTF-8 sequence', 5);
        }

        $value = json_decode($json);

        if ($value === NULL
            && $json !== ''  // it doesn't clean json_last_error flag until 5.3.7
            && $json !== 'null' // in this case NULL is not failure
        ) {
            $error = json_last_error();
            $message = isset(static::$messages[$error]) ? static::$messages[$error] : 'Unknown error';
            //throw new JsonException($message, $error);
            print_r($error);
        }
        return $value;
    }
    
    
    
    
    
}

?>
