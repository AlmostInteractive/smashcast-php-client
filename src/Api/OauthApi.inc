<?php

declare(strict_types=1);

namespace SmashcastApi\Api;

use GuzzleHttp\Client;
use GuzzleHttp\Exception\GuzzleException;
use GuzzleHttp\Psr7\Request;
use GuzzleHttp\RequestOptions;
use Psr\Http\Message\ResponseInterface;

class OauthApi extends AbstractApiBase
{
    private const AUTH_ENDPOINT = 'https://api.smashcast.tv/oauth/login';

    private $appSecret;

    public function __construct(string $appName, string $appToken, string $appSecret, Client $guzzleClient)
    {
        parent::__construct($appName, $appToken, $guzzleClient);
        $this->appSecret = $appSecret;
    }

    /**
     * @return string A full authentication URL, including the Guzzle client's base URI.
     */
    public function getAuthUrl(bool $forceVerify = false, ?string $state = null): string
    {
        return sprintf(
            '%s%s',
            self::AUTH_ENDPOINT,
            $this->getPartialAuthUrl($forceVerify, $state)
        );
    }

    /**
     * @throws GuzzleException
     */
    public function getUserAccessToken(string $requestToken): ResponseInterface
    {
        $hash = base64_encode($this->appToken . $this->appSecret);

        return $this->apiPost('oauth/exchange',
            [
                'request_token' => $requestToken,
                'app_token' => $this->appToken,
                'hash' => $hash
            ]);
    }

    /**
     * @throws GuzzleException
     */
    public function isValidAccessToken(string $accessToken): bool
    {
        $response = $this->apiGet(
            'auth/valid/' . $this->appName,
            ['token' => $accessToken]
        );
        $data = json_decode($response->getBody()->getContents(), true);
        return $data['success'] === true;
    }

    /**
     * @return string A partial authentication URL, excluding the Guzzle client's base URI.
     */
    private function getPartialAuthUrl(bool $forceVerify = false, ?string $state = null): string
    {
        $optionalParameters = '';
        $optionalParameters .= $forceVerify ? '&force_auth=force' : '';
        $optionalParameters .= $state ? sprintf('&state=%s', $state) : '';

        return sprintf(
            '?app_token=%s%s',
            $this->appToken,
            $optionalParameters
        );
    }
}
