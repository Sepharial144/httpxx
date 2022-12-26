#ifndef _HTTPXX_DECODER_DEFINITIONS_HPP_
#define _HTTPXX_DECODER_DEFINITIONS_HPP_

#define HTTPXX_DECODER_LIMIT_PACKET 10u
#define HTTPXX_DECODER_MAX_REQ_SHIFT 3u
#define HTTPXX_DECODER_REQ_MAX_SIZE 150u
#define HTTPXX_DECODER_ERROR -1

// find first readable letter
#define HTTPXX_DECODER_SPACE_LETTER 32u
#define HTTPXX_DECODER_FIRST_READABLE_LETTER 33u
#define HTTPXX_DECODER_LAST_READABLE_LETTER 126u
#define HTTPXX_DECODER_UNREADABLE_LETTERS 31u
#define HTTPXX_DECODER_DEL_LETTER 127u

// detecting request
#define HTTPXX_REQUEST_GET_LEFT 140u
#define HTTPXX_REQUEST_GET_RIGHT 153u
#define HTTPXX_REQUEST_POST_LEFT 159u
#define HTTPXX_REQUEST_POST_RIGHT 162u
#define HTTPXX_REQUEST_PUT_LEFT 165u
#define HTTPXX_REQUEST_PUT_RIGHT 169u
#define HTTPXX_REQUEST_PATCH_LEFT 145u
#define HTTPXX_REQUEST_PATCH_RIGHT 149u
#define HTTPXX_REQUEST_DELETE_LEFT 137u
#define HTTPXX_REQUEST_DELETE_RIGHT 145u
#define HTTPXX_REQUEST_COPY_LEFT 146u
#define HTTPXX_REQUEST_COPY_RIGHT 159u
#define HTTPXX_REQUEST_HEAD_LEFT 141u
#define HTTPXX_REQUEST_HEAD_RIGHT 134u
#define HTTPXX_REQUEST_OPTIONS_LEFT 159u
#define HTTPXX_REQUEST_OPTIONS_RIGHT 164u
#define HTTPXX_REQUEST_LINK_LEFT 149u
#define HTTPXX_REQUEST_LINK_RIGHT 151u
#define HTTPXX_REQUEST_UNLINK_LEFT 163u
#define HTTPXX_REQUEST_UNLINK_RIGHT 151u
#define HTTPXX_REQUEST_PURGE_LEFT 165u
#define HTTPXX_REQUEST_PURGE_RIGHT 167u
#define HTTPXX_REQUEST_LOCK_LEFT 155u
#define HTTPXX_REQUEST_LOCK_RIGHT 146u
#define HTTPXX_REQUEST_UNLOCK_LEFT 163u
#define HTTPXX_REQUEST_UNLOCK_RIGHT 157u
#define HTTPXX_REQUEST_PROPFIND_LEFT 162u
#define HTTPXX_REQUEST_PROPFIND_RIGHT 161u
#define HTTPXX_REQUEST_VIEW_LEFT 159u
#define HTTPXX_REQUEST_VIEW_RIGHT 142u

#endif